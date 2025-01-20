/*
    P55 (**) Construct completely balanced binary trees.
    this is an exercise to create a balanced binary tree given the number of nodes
    give all possible solutions
 */

def cBalancedTree(n: Int, v: String = "x"): List[Tree[String]] = {
  if n == 0 then List(EndNode)
  else {
    if n % 2 == 1 then {
      val subTrees = cBalancedTree(n / 2)
      for {
        subTree1 <- subTrees
        subTree2 <- subTrees
      } yield Node(v, subTree1, subTree2)
    } else
      for {
        subTree1 <- cBalancedTree(n/ 2)
        subTree2 <- cBalancedTree(n / 2 - 1)
        combinedTree <- List(
          Node(v, subTree1, subTree2),
          Node(v, subTree2, subTree1)
        )
      } yield combinedTree
  }
}

object P55Demo extends App {
    println(cBalancedTree(4))
}
