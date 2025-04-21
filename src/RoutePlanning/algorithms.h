#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../DataStructures/Graph.h"
#include "route.h"

class Algorithms {
 public:
  template <class T>
  static Route get_best_driving_route(Graph<T>* g, const T& source,
                                      const T& destination);
  template <class T>
  static Route get_best_alternative_driving_route(
      Graph<T>* g, const std::vector<T>& best_route, const T& source,
      const T& destination);

  template <class T>
  static Route get_restricted_route(
      Graph<T>* g, const T& source, const T& destination,
      const std::vector<T>& avoid_locations,
      const std::vector<std::pair<T, T>>& avoid_edges,
      const std::vector<T>& include_location);

  template <class T>
  static std::pair<Route, Route> get_best_driving_walking_route(
      Graph<T>* driving_g, Graph<T>* walking_g, const T& source,
      const T& destination, double max_walk_time,
      const std::vector<T>& avoid_locations,
      const std::vector<std::pair<T, T>>& avoid_edges,
      const std::unordered_map<std::string, Location>& code_location_map,
      const bool& get_suggestions, const size_t& num_suggestions,
      bool& parking_exists, bool& walking_route_within_time_exists,
      bool& driving_route_exists,
      std::vector<std::pair<Route, Route>>& suggestions);

 private:
  template <class T>
  static bool relax(Vertex<T>* v, Edge<T>* edge);

  template <class T>
  static Route getPath(Graph<T>* g, const T& source, const T& dest,
                       const bool& reverse);

  // Dijkstra's algorithm for shortest path
  template <class T>
  static Route dijkstras_algorithm(Graph<T>* g, const T& source,
                                   const T& destination);

  template <class T>
  static void dijkstras_algorithm(Graph<T>* g, const T& source,
                                  std::unordered_map<T, double>& distances);

  template <class T>
  static void process_suggestion(
      Graph<T>* driving_g,
      const std::unordered_map<T, double>& driving_distances,
      const Route& walking_route, const T& source,
      std::vector<std::pair<Route, Route>>& suggestions,
      const size_t& num_suggestions);
};

/** @brief Relax function updates the distance and path if a shorter path is found.
 *  Complexity: O(1)
 */
template <class T>
bool Algorithms::relax(Vertex<T>* v, Edge<T>* edge) {
  Vertex<T>* u = edge->getDest();
  double newDist = v->getDist() + edge->getWeight();

  if (newDist < u->getDist()) {
    u->setDist(newDist);
    u->setPath(edge);
    return true;
  }
  return false;
}
/** @brief gets the route between a source and a destination of a graph, optionally reversed
 * @tparam T Type of vertex information
 * @param g Graph containing the path
 * @param source Starting vertex
 * @param dest Destination vertex
 * @param reverse Whether to return path in reverse order
 *  Complexity: O(n)
*/
template <class T>
Route Algorithms::getPath(Graph<T>* g, const T& source, const T& dest,
                          const bool& reverse) {
  std::vector<T> location_codes;
  double weight = 0;
  Vertex<T>* v = g->findVertex(dest);
  if (v == nullptr || v->getDist() == INF) {
    weight = INF;
    return Route(source, dest, location_codes, weight);  // no path exists
  }

  while (v != nullptr) {
    if (reverse) {
      location_codes.push_back(v->getInfo());
    } else {
      location_codes.insert(location_codes.begin(), v->getInfo());
    }
    Edge<T>* path = v->getPath();
    if (path == nullptr) break;
    weight += path->getWeight();
    v = path->getOrig();
  }

  return Route(source, dest, location_codes, weight);
}

template <class T>
Route Algorithms::dijkstras_algorithm(Graph<T>* g, const T& source,
                                      const T& destination) {
  for (Vertex<T>* v : g->getVertexSet()) {
    v->setDist(INF);
    v->setPath(nullptr);
    v->setVisited(false);
    v->setQueueIndex(0);
  }

  Vertex<T>* start = g->findVertex(source);
  if (start == nullptr)
    return Route(source, destination, {}, INF);  // source node does not exist
  start->setDist(0);

  MutablePriorityQueue<Vertex<T>> q;
  q.insert(start);

  while (!q.empty()) {
    Vertex<T>* v = q.extractMin();
    v->setVisited(true);
    if (v->getInfo() == destination) break;

    for (Edge<T>* edge : v->getAdj()) {
      Vertex<T>* u = edge->getDest();
      if (!u->isVisited() && relax(v, edge)) {
        if (u->getQueueIndex() == 0) {
          q.insert(u);
        } else {
          q.decreaseKey(u);
        }
      }
    }
  }

  return getPath(g, source, destination, false);
}
/** @brief function to determine the best independent driving route by calling
 * the dijkstras_algorithm and returning the best route.
 * @param g graph
 * @param source info of the source node
 * @param destination info of the destination node
 * @return best possible route
 * Complexity: Same as dijkstras
*/
template <class T>
Route Algorithms::get_best_driving_route(Graph<T>* g, const T& source,
                                         const T& destination) {
  Route best_route = dijkstras_algorithm(g, source, destination);
  return best_route;
}
/** @paragraph
 * function to determine the second best driving route by calling creating a copy of the 
 * original graph and removing the edges and intermediary nodes part of the best possible route and then calling
 * the dijkstras_algorithm on this altered graph.
 * @param g graph
 * @param best_route best possible path from source to destination
 * @param source info of the source node
 * @param destination info of the destination node
 * @return second best possible route
 * Complexity:  O(|V| + |E|) for copy + O(|E| + |V|log|V|) for Dijkstra's
*/
template <class T>
Route Algorithms::get_best_alternative_driving_route(
    Graph<T>* g, const std::vector<T>& best_route, const T& source,
    const T& destination) {
  if (best_route.empty()) return Route(source, destination, {}, INF);
  Graph<T>* alternative_g = new Graph<T>(*g);

  // remove edges and intermediary locations from the graph
  for (size_t i = 0; i < best_route.size() - 1; i++) {
    T v1_info = best_route[i];
    T v2_info = best_route[i + 1];
    alternative_g->removeEdge(v1_info, v2_info);
    alternative_g->removeEdge(v2_info, v1_info);
    if (v1_info != source) {
      alternative_g->removeVertex(v1_info);
    };
  }

  // get the second best route
  Route second_best_route =
      dijkstras_algorithm(alternative_g, source, destination);

  delete alternative_g;

  return second_best_route;
}
/** @paragraph
 * function to determine the second best driving route by calling creating a copy of the 
 * original graph and removing the edges from the avoid_edges and nodes from the avoid_nodes .
 * If there is no include location, return the best route using the djisktra algorithm else
 * do one djisktra from the source to the include node represented by source_to_inclide and 
 * then do one from the include to the destination and then create a new route by joining
 * these two routes.
 * @param g graph
 * @param source info of the source node
 * @param destination info of the destination node
 * @param max_walk_time maximum walking time allowed
 * @param avoid_locations vector of the locations that are restricted
 * @param avoid_edges vector of the edges that are restricted
 * @param include_location vector of the locations that must be apart of the route
 * @return best possible restricted route
 * Complexity: O(|V| + |E|) for copy + up to 2x Dijkstra's complexity
*/
template <class T>
Route Algorithms::get_restricted_route(
    Graph<T>* g, const T& source, const T& destination,
    const std::vector<T>& avoid_locations,
    const std::vector<std::pair<T, T>>& avoid_edges,
    const std::vector<T>& include_location) {
  // if there are no restrictions, return the best route
  if (avoid_locations.empty() && avoid_edges.empty() &&
      include_location.empty()) {
    Route restricted_route = dijkstras_algorithm(g, source, destination);
    return restricted_route;
  }

  // if there is more than one include location, return INF Route
  if (include_location.size() > 1) {
    return Route(source, destination, {}, INF);
  }

  Graph<T>* restricted_g = new Graph<T>(*g);

  for (const T& location : avoid_locations) {
    // if the source or destination is in the avoid_locations, return INF Route
    if (location == source || location == destination) {
      delete restricted_g;
      return Route(source, destination, {}, INF);
    }
    restricted_g->removeVertex(location);
  }

  for (const auto& edge : avoid_edges) {
    restricted_g->removeEdge(edge.first, edge.second);
    restricted_g->removeEdge(edge.second, edge.first);
  }

  if (include_location.empty()) {
    // if there is no include location, return the best route
    Route restricted_route =
        dijkstras_algorithm(restricted_g, source, destination);
    delete restricted_g;
    return restricted_route;
  }

  Route source_to_include =
      dijkstras_algorithm(restricted_g, source, include_location[0]);

  Route include_to_dest =
      dijkstras_algorithm(restricted_g, include_location[0], destination);

  delete restricted_g;

  // if there is no path from source to include_location or include_location to
  // destination, return INF Route
  if (source_to_include.get_weight() == INF ||
      include_to_dest.get_weight() == INF) {
    return Route(source, destination, {}, INF);
  }

  std::vector<T> location_codes = source_to_include.get_location_codes();
  if (!location_codes.empty()) {
    location_codes.pop_back();  // remove the last element (include_location)
  }

  std::vector<T> include_to_dest_codes = include_to_dest.get_location_codes();
  location_codes.insert(location_codes.end(), include_to_dest_codes.begin(),
                        include_to_dest_codes.end());

  double weight = source_to_include.get_weight() + include_to_dest.get_weight();

  Route restricted_route = Route(source, destination, location_codes, weight);
  return restricted_route;
}
/**
 * @paragraph 
 * In this function we determine the best driving-walking route in a pair of routes. Two graphs are 
 * created, one, restricted_walking_g, is a copy of walking_g and the other, restricted_driving_g,
 * is a copy of driving_g. Any edges or intermediary locations that are possibly in avoid_locations
 * or avoid_edges are removed from this new graphs. Precomputed walking distances from destination 
 * and driving distances from source. Then iterates through all parking locations skipping those
 * without parking, checking if walking distances is within the limit and checks driving distance from source
 *  @tparam T Type of vertex information
 * @param driving_g Driving graph
 * @param walking_g Walking graph
 * @param source Starting location
 * @param destination Target location
 * @param max_walk_time Maximum allowed walking time
 * @param avoid_locations Locations to avoid
 * @param avoid_edges Edges to avoid
 * @param code_location_map Map of location codes to Location objects
 * @param get_suggestions Whether to return alternative suggestions
 * @param num_suggestions Maximum number of suggestions to return
 * @param parking_exists Output flag indicating if parking exists
 * @param walking_route_within_time_exists Output flag for valid walking routes
 * @param driving_route_exists Output flag for valid driving routes
 * @param suggestions Output vector for alternative route suggestions
 * @return a pair of the best driving route and the best walking route
 * Complexity: O(nlog(n))
 * 
 */
template <class T>
std::pair<Route, Route> Algorithms::get_best_driving_walking_route(
    Graph<T>* driving_g, Graph<T>* walking_g, const T& source,
    const T& destination, double max_walk_time,
    const std::vector<T>& avoid_locations,
    const std::vector<std::pair<T, T>>& avoid_edges,
    const std::unordered_map<std::string, Location>& code_location_map,
    const bool& get_suggestions, const size_t& num_suggestions,
    bool& parking_exists, bool& walking_route_within_time_exists,
    bool& driving_route_exists,
    std::vector<std::pair<Route, Route>>& suggestions) {
  T best_parking_location;
  Route best_driving_route(source, destination, {}, INF);
  Route best_walking_route(source, destination, {}, INF);
  double min_total_weight = INF;

  suggestions.clear();
  parking_exists = walking_route_within_time_exists = driving_route_exists =
      false;

  // Create restricted graphs
  Graph<T>* restricted_walking_g = new Graph<T>(*walking_g);
  Graph<T>* restricted_driving_g = new Graph<T>(*driving_g);

  for (const T& location : avoid_locations) {
    if (location == source || location == destination) {
      delete restricted_walking_g;
      delete restricted_driving_g;
      // return INF Route pair
      return std::make_pair(best_driving_route, best_walking_route);
    }
    restricted_walking_g->removeVertex(location);
    restricted_driving_g->removeVertex(location);
  }
  for (const auto& edge : avoid_edges) {
    restricted_walking_g->removeEdge(edge.first, edge.second);
    restricted_walking_g->removeEdge(edge.second, edge.first);
    restricted_driving_g->removeEdge(edge.first, edge.second);
    restricted_driving_g->removeEdge(edge.second, edge.first);
  }

  // precompute shortest paths from destination (for walking) and from source
  // (for driving)
  std::unordered_map<T, double> walking_distances;
  std::unordered_map<T, double> driving_distances;
  dijkstras_algorithm(restricted_walking_g, destination, walking_distances);
  dijkstras_algorithm(restricted_driving_g, source, driving_distances);

  for (Vertex<T>* parking_vertex : restricted_walking_g->getVertexSet()) {
    T parking_location = parking_vertex->getInfo();

    if (!code_location_map.at(parking_location).get_has_parking()) continue;
    parking_exists = true;

    double walking_weight = walking_distances[parking_location];
    if (get_suggestions) {
      if (walking_weight > max_walk_time) {
        Route walking_route =
            getPath(restricted_walking_g, destination, parking_location, true);
        process_suggestion(restricted_driving_g, driving_distances,
                           walking_route, source, suggestions, num_suggestions);
      } else {
        continue;
      }

    } else {
      if (walking_weight > max_walk_time) {
        continue;
      }

      walking_route_within_time_exists = true;
      double driving_weight = driving_distances[parking_location];
      if (driving_weight == INF) continue;

      driving_route_exists = true;
      double total_weight = driving_weight + walking_weight;

      if (total_weight < min_total_weight) {
        min_total_weight = total_weight;
        best_parking_location = parking_location;
      }
    }
  }
  if (get_suggestions) {
    delete restricted_driving_g;
    delete restricted_walking_g;
    // return INF Route pair
    return std::make_pair(best_driving_route, best_walking_route);
  }
  best_driving_route =
      getPath(restricted_driving_g, source, best_parking_location, false);
  best_walking_route =
      getPath(restricted_walking_g, destination, best_parking_location, true);
  delete restricted_driving_g;
  delete restricted_walking_g;

  return std::make_pair(best_driving_route, best_walking_route);
}
/** @paragraph 
 * In this function we return the best possible suggestions for the driving-walking problem
 * if there is no best solution. We calcultate the driving distance from source to parking
 * location that is obtained as the source of the walking_route. If there is a possible driving route
 * then we add the pair of routes to the suggestions vector sort the elements and truncate
 * to mantain num_suggestions size
 * @tparam T Type of vertex information
 * @param driving_g driving graph
 * @param walking_route the route from the parking node to the destination
 * @param source the info of the source node
 * @param suggestions the vector where the alternative routes will be added
 * @param num_suggestions number of suggestions allowed
 * @return void
 * Complexity: O(nlog(n))
 */
template <class T>
void Algorithms::process_suggestion(
    Graph<T>* driving_g, const std::unordered_map<T, double>& driving_distances,
    const Route& walking_route, const T& source,
    std::vector<std::pair<Route, Route>>& suggestions,
    const size_t& num_suggestions) {
  // If no walking route exists, we can't make any suggestions
  if (walking_route.get_weight() == INF) {
    return;
  }

  // Calculate the total driving distance to the parking location
  T parking_location =
      walking_route.get_location_codes()
          .front();  // last location of walking route is parking
  double driving_weight = driving_distances.at(parking_location);

  // If there's no valid driving weight or no parking exists, no suggestion can
  // be made
  if (driving_weight == INF) {
    return;
  }

  // Create the suggestion pair (driving route, walking route)
  Route driving_route = getPath(driving_g, source, parking_location, false);
  suggestions.push_back(std::make_pair(driving_route, walking_route));

  // Sort suggestions to maintain the best suggestions at the beginning
  if (suggestions.size() > num_suggestions) {
    std::sort(
        suggestions.begin(), suggestions.end(),
        [](const std::pair<Route, Route>& a, const std::pair<Route, Route>& b) {
          return (a.first.get_weight() + a.second.get_weight()) <
                 (b.first.get_weight() + b.second.get_weight());
        });
    suggestions.resize(
        num_suggestions);  // Keep only top num_suggestions results
  }
}

/** @brief Modified Dijkstra's algorithm that populates a distance map by storing the final distances in a output map
 *  @tparam T Type of vertex information
 *  @param g Graph to process
 *  @param source Starting vertex
 *  @param distances Output map storing distances from source to all vertices
 * Complexity: O(|E| + |V|log|V|) using Fibonacci heap
*/
template <class T>
void Algorithms::dijkstras_algorithm(Graph<T>* g, const T& source,
                                     std::unordered_map<T, double>& distances) {
  for (Vertex<T>* v : g->getVertexSet()) {
    v->setDist(INF);
    v->setPath(nullptr);
    v->setVisited(false);
    v->setQueueIndex(0);
  }

  Vertex<T>* start = g->findVertex(source);
  if (!start) return;
  start->setDist(0);

  MutablePriorityQueue<Vertex<T>> q;
  q.insert(start);

  while (!q.empty()) {
    Vertex<T>* v = q.extractMin();
    v->setVisited(true);
    distances[v->getInfo()] = v->getDist();

    for (Edge<T>* edge : v->getAdj()) {
      Vertex<T>* u = edge->getDest();
      if (!u->isVisited() && relax(v, edge)) {
        if (u->getQueueIndex() == 0) {
          q.insert(u);
        } else {
          q.decreaseKey(u);
        }
      }
    }
  }
}

#endif
