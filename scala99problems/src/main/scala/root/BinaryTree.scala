package root

import trees.{ShapeBTsExercises, TreeOps, CreateBTsExercises}

sealed trait Tree[+T] {
    def isMirror: Boolean = ShapeBTsExercises.isMirroredStructure(this)
    def isSimilarTo[U](t: Tree[U]): Boolean =
        ShapeBTsExercises.haveSameStructure(this, t)
    def isMirrorTo[U](t: Tree[U]): Boolean =
        ShapeBTsExercises.haveMirrorStructure(this, t)
    def countNodes: Int = TreeOps.countNodes(this)
    def countLeafs: Int = TreeOps.countLeaf(this)
    def collectLeafs: List[T] = TreeOps.collectLeaves(this)
    def collectInternalNodes: List[T] = TreeOps.collectInternalNodes(this)
    def collectNodesAtLevel(level: Int): List[T] =
        TreeOps.collectNodesAtLevel(this, level)
    def maxDepth: Int
    def leftMostDepth: Int
}

case class Node[+T](value: T, left: Tree[T], right: Tree[T]) extends Tree[T] {
    override def toString(): String =
        "T(" + value.toString + " " + left.toString + " " + right.toString + ")"
    def maxDepth: Int = left.maxDepth max right.maxDepth + 1
    def leftMostDepth: Int = left.leftMostDepth + 1
}

case object EndNode extends Tree[Nothing] {
    override def toString(): String = "."

    val bounds = List((0, 0))
    def maxDepth: Int = 0
    def leftMostDepth: Int = 0
}

object Node {
    def apply[T](value: T, left: Tree[T] = EndNode, right: Tree[T] = EndNode) =
        new Node(value, left, right)
}

object Tree {
    def createCompletelyBalancedBTs[T](nodesCount: Int, value: T = "x") =
        CreateBTsExercises.completelyBalancedBTs(value)(nodesCount)
    def createSymmetricCompletelyBalancedBTs[T](
        nodesCount: Int,
        value: T = "x"
    ) = CreateBTsExercises.symmetricCompletelyBalancedBTs(value)(nodesCount)
}

class PositionedNode[T](v: T, l: Tree[T], r: Tree[T], val x: Int, val y: Int)
    extends Node(v, l, r)

type PositionedTree[T] = PositionedNode[T] | EndNode.type

// in case we want to add methods to this typealia, extend with typeclass
extension[T](a: PositionedTree[T])
    def abc: Unit = println("abc")


object demoo extends App{
    val a: PositionedTree[Int] = PositionedNode(1,EndNode,EndNode,5,3)
    // exhaustive pattern matching
    a match
        case a: PositionedNode[Int] => println("p node")
        case EndNode => println("end")
    
}