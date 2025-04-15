import org.scalatest.funsuite.AnyFunSuite
import org.scalatest.matchers.should.Matchers

class BfsShortestPathTest extends AnyFunSuite with Matchers {
  import GraphBFS._
  test("Empty graph should return None") {
    val emptyGraph: Map[Int, List[Int]] = Map()
    bfsShortestPathUnweightedG(emptyGraph, 1, 5) shouldBe None
  }

  test("Path to self should return just the start node") {
    val graph = Map(1 -> List(2, 3), 2 -> List(1, 4), 3 -> List(1), 4 -> List(2))
    bfsShortestPathUnweightedG(graph, 1, 1) shouldBe Some(List(1))
  }

  test("Direct edge between start and target") {
    val graph = Map(1 -> List(2), 2 -> List(1))
    bfsShortestPathUnweightedG(graph, 1, 2) shouldBe Some(List(1, 2))
  }

  test("Path with multiple nodes") {
    val graph = Map(
      1 -> List(2, 3),
      2 -> List(1, 4),
      3 -> List(1, 5),
      4 -> List(2, 6),
      5 -> List(3, 6),
      6 -> List(4, 5)
    )
    bfsShortestPathUnweightedG(graph, 1, 6) shouldBe Some(List(1, 2, 4, 6))
    // Or Some(List(1, 2, 4, 6)) - either is valid as shortest path
  }

  test("No path exists") {
    val graph = Map(
      1 -> List(2, 3),
      2 -> List(1),
      3 -> List(1),
      4 -> List(5),
      5 -> List(4)
    )
    bfsShortestPathUnweightedG(graph, 1, 4) shouldBe None
  }

  test("Complex graph with multiple possible paths") {
    val graph = Map(
      1 -> List(2, 3, 4),
      2 -> List(1, 5, 6),
      3 -> List(1, 7),
      4 -> List(1, 8),
      5 -> List(2, 9),
      6 -> List(2, 10),
      7 -> List(3, 11),
      8 -> List(4, 11),
      9 -> List(5, 12),
      10 -> List(6, 12),
      11 -> List(7, 8, 12),
      12 -> List(9, 10, 11)
    )
    val path = bfsShortestPathUnweightedG(graph, 1, 12)
    path.isDefined shouldBe true
    path.get.head shouldBe 1
    path.get.last shouldBe 12
    path.get.length shouldBe 5 // shortest path has 4 nodes (e.g., 1-2-5-9-12 or similar)
  }

  test("Start node not in graph") {
    val graph = Map(2 -> List(3), 3 -> List(2))
    bfsShortestPathUnweightedG(graph, 1, 2) shouldBe None
  }

  test("Target node not in graph") {
    val graph = Map(1 -> List(2), 2 -> List(1))
    bfsShortestPathUnweightedG(graph, 1, 3) shouldBe None
  }

  test("Graph with a cycle") {
    val graph = Map(
      1 -> List(2),
      2 -> List(3, 1),
      3 -> List(4, 2),
      4 -> List(5, 3),
      5 -> List(4)
    )
    bfsShortestPathUnweightedG(graph, 1, 5) shouldBe Some(List(1, 2, 3, 4, 5))
  }
}