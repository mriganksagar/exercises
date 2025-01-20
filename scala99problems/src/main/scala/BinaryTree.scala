sealed trait Tree[+T]

case class Node[+T](value: T, left: Tree[T], right: Tree[T]) extends Tree[T]:
    override def toString(): String = "T(" + value.toString + " " + left.toString + " " + right.toString + ")"

case object EndNode extends Tree[Nothing]:
    override def toString(): String = "."

object Node{
    def apply[T](value: T, left: Tree[T] = EndNode, right: Tree[T] = EndNode) = new Node(value, left, right)
}


object Tree {
    def createCompletelyBalancedBTs[T](nodesCount: Int, value:T = "x") = CreateBTsExercises.completelyBalancedBTs(value)(nodesCount)
}