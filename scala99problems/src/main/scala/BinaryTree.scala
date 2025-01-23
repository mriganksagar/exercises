sealed trait Tree[+T]{
    def isMirror: Boolean = ShapeBTsExercises.isMirroredStructure(this)
    def isSimilarTo[U](t: Tree[U]): Boolean = ShapeBTsExercises.haveSameStructure(this, t)
    def isMirrorTo[U](t: Tree[U]): Boolean = ShapeBTsExercises.haveMirrorStructure(this, t)
    def countNodes: Int = TreeOps.countNodes(this)
    def countLeafs: Int = TreeOps.countLeaf(this)
    def collectLeafs: List[T] = TreeOps.collectLeaves(this)
    def collectInternalNodes: List[T] = TreeOps.collectInternalNodes(this)
    def collectNodesAtLevel(level: Int): List[T] = TreeOps.collectNodesAtLevel(this, level)
    def maxDepth: Int
    def leftMostDepth: Int
}

case class Node[+T](value: T, left: Tree[T], right: Tree[T]) extends Tree[T]{
    override def toString(): String = "T(" + value.toString + " " + left.toString + " " + right.toString + ")"
    def maxDepth: Int = left.maxDepth max right.maxDepth +1
    def leftMostDepth: Int = left.leftMostDepth +1
}

case object EndNode extends Tree[Nothing]{
    override def toString(): String = "."
    def maxDepth: Int = 0
    def leftMostDepth: Int = 0
}

object Node{
    def apply[T](value: T, left: Tree[T] = EndNode, right: Tree[T] = EndNode) = new Node(value, left, right)
}


object Tree {
    def createCompletelyBalancedBTs[T](nodesCount: Int, value:T = "x") = CreateBTsExercises.completelyBalancedBTs(value)(nodesCount)
    def createSymmetricCompletelyBalancedBTs[T](nodesCount: Int, value:T = "x") = CreateBTsExercises.symmetricCompletelyBalancedBTs(value)(nodesCount)
}