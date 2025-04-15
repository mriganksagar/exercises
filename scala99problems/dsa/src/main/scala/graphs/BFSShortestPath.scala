// given a station and its neighbouring station


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
}

