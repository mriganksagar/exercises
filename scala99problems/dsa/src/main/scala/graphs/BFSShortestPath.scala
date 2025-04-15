// given a station and its neighbouring station
import scala.collection.immutable.TreeMap


object GraphBFS {
  def bfsShortestPathUnweightedG(graph: Map[Int, List[Int]], start: Int, target: Int): Option[List[Int]] = {
    
    def aux(s: List[List[Int]], t : Int, visited: Set[Int]): Option[List[Int]] = 
      if s == Nil then None
      else s.find(_.head == t).orElse {
        val nextBreadth = s.flatMap{ l =>
            graph.getOrElse(l.head, Nil).collect{
              case e if !visited.contains(e) => e::l
              }
          }.filterNot(_.isEmpty)
        aux(nextBreadth, t, visited ++ nextBreadth.map(_.head).toSet)
      }
    aux(List(List(start)), target, Set(start)).map(_.reverse)
  }  
  
  // I am considering positive weights
  case class Edge(weight: Int, to: Int)
  type Graph = Map[Int, List[Edge]] 
  case class Path(cost: Int, path: List[Int])
  def bfsShortestPathWeightedG(graph: Graph, start: Int, target: Int): Option[List[Int]] = {
    given Ordering[(Int, Path)] with {
      def compare(x: (Int, Path), y: (Int, Path)): Int = x._2.cost - y._2.cost
    }
      
    def aux(paths: TreeMap[Int, Path], visited: Set[Int]): Option[Path] = paths.minOption.flatMap{
        case (to, path) if to == target => Some(path)
        case (to, path) => {
          val unvisitedNeighbors = graph.getOrElse(to, Nil).filterNot(edge => visited(edge.to))
          val newPaths = unvisitedNeighbors.foldLeft(paths.removed(to)){
              (_paths, edge) => _paths.updatedWith(edge.to){
                  case s @ Some(Path(cost, _)) if cost <= edge.weight + path.cost => s
                  case _ => Some(Path(path.cost + edge.weight, edge.to::path.path))
                }
            }  
          aux(newPaths, visited + to)
        }
      }
    aux(TreeMap(start -> Path(0, List(start))), Set.empty).map(_.path.reverse)
  }
}

