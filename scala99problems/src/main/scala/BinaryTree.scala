sealed trait Tree[+T]{
    def isMirror: Boolean = ShapeBTsExercises.isMirroredStructure(this)
    def isSimilarTo[U](t: Tree[U]): Boolean = ShapeBTsExercises.haveSameStructure(this, t)
    def isMirrorTo[U](t: Tree[U]): Boolean = ShapeBTsExercises.haveMirrorStructure(this, t)
}

case class Node[+T](value: T, left: Tree[T], right: Tree[T]) extends Tree[T]:
    override def toString(): String = "T(" + value.toString + " " + left.toString + " " + right.toString + ")"

case object EndNode extends Tree[Nothing]:
    override def toString(): String = "."

object Node{
    def apply[T](value: T, left: Tree[T] = EndNode, right: Tree[T] = EndNode) = new Node(value, left, right)
}


object Tree {
    def createCompletelyBalancedBTs[T](nodesCount: Int, value:T = "x") = CreateBTsExercises.completelyBalancedBTs(value)(nodesCount)
    def createSymmetricCompletelyBalancedBTs[T](nodesCount: Int, value:T = "x") = CreateBTsExercises.symmetricCompletelyBalancedBTs(value)(nodesCount)
}