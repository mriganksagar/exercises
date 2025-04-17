// given a station and its neighbouring station
import scala.collection.immutable.TreeMap

object GraphBFS {
  def bfsShortestPathUnweightedG(
      graph: Map[Int, List[Int]],
      start: Int,
      target: Int
  ): Option[List[Int]] = {

    def aux(s: List[List[Int]], t: Int, visited: Set[Int]): Option[List[Int]] =
      if s == Nil then None
      else
        s.find(_.head == t).orElse {
          val nextBreadth = s
            .flatMap { l =>
              graph.getOrElse(l.head, Nil).collect {
                case e if !visited.contains(e) => e :: l
              }
            }
            .filterNot(_.isEmpty)
          aux(nextBreadth, t, visited ++ nextBreadth.map(_.head).toSet)
        }
    aux(List(List(start)), target, Set(start)).map(_.reverse)
  }

  // I am considering positive weights
  case class Edge(weight: Int, to: Int)
  type Graph = Map[Int, List[Edge]]
  case class Path(cost: Int, path: List[Int])
  given Ordering[(Int, Path)] with {
    def compare(x: (Int, Path), y: (Int, Path)): Int = x._2.cost - y._2.cost
  }
  def bfsShortestPathWeightedG(
      graph: Graph,
      start: Int,
      target: Int
  ): Option[List[Int]] = {

    def aux(paths: TreeMap[Int, Path], visited: Set[Int]): Option[Path] =
      paths.minOption.flatMap {
        case (to, path) if to == target => Some(path)
        case (to, path) => {
          val unvisitedNeighbors =
            graph.getOrElse(to, Nil).filterNot(edge => visited(edge.to))
          val newPaths = unvisitedNeighbors.foldLeft(paths.removed(to)) {
            (_paths, edge) =>
              _paths.updatedWith(edge.to) {
                case s @ Some(Path(cost, _))
                    if cost <= edge.weight + path.cost =>
                  s
                case _ =>
                  Some(Path(path.cost + edge.weight, edge.to :: path.path))
              }
          }
          aux(newPaths, visited + to)
        }
      }
    aux(TreeMap(start -> Path(0, List(start))), Set.empty).map(_.path.reverse)
  }

  // returns LazyList of all paths; path is: target -> Path(weight, path)
  def bfsShortestPaths(graph: Graph)(start: Int): LazyList[(Int, Path)] = {
    def aux(
        paths: TreeMap[Int, Path],
        visited: Set[Int]
    ): LazyList[(Int, Path)] = paths.minOption match
      case None => LazyList.empty
      case Some(selectedPath) =>
        selectedPath #:: {
          val (node, path) = selectedPath
          val nextPaths = graph
            .getOrElse(node, Nil)
            .filterNot(edge => visited(edge.to) && edge.to == node)
            .foldLeft(paths.removed(node)) { (_paths, edge) =>
              _paths.updatedWith(edge.to) {
                case s @ Some(Path(cost, _))
                    if cost <= edge.weight + path.cost =>
                  s
                case _ =>
                  Some(Path(path.cost + edge.weight, edge.to :: path.path))
              }
            }
          aux(nextPaths, visited + node)
        }

    aux(TreeMap(start -> Path(0, List(start))), Set.empty).map(p =>
      p._1 -> p._2.copy(path = p._2.path.reverse) // left to right i.e target
    )
  }
}
