/*
    P55 (**) Construct completely balanced binary trees.
    this is an exercise to create a balanced binary tree given the number of nodes
    give all possible solutions
 */
import CreateBTsExercises.constructHeightBalancedBTs
import scala.annotation.tailrec

object CreateBTsExercises {
    def completelyBalancedBTs[T](v: T)(n: Int): List[Tree[T]] = {
        if n == 0 then List(EndNode)
        else {
            if n % 2 == 1 then {
                val subTrees = completelyBalancedBTs(v)(n / 2)
                for {
                    subTree1 <- subTrees
                    subTree2 <- subTrees
                } yield Node(v, subTree1, subTree2)
            } else
                for {
                    subTree1 <- completelyBalancedBTs(v)(n / 2)
                    subTree2 <- completelyBalancedBTs(v)(n / 2 - 1)
                    combinedTree <- List(
                      Node(v, subTree1, subTree2),
                      Node(v, subTree2, subTree1)
                    )
                } yield combinedTree
        }
    }

    // P58
    import ShapeBTsExercises._
    def symmetricCompletelyBalancedBTs[T](v: T)(n: Int): List[Tree[T]] =
        completelyBalancedBTs(v)(n).filter(isMirroredStructure)

    /*
        P59: contruct height balanced binary trees
        that means in no tree the height difference between left and right subtree
        should be no greater than 1

        solution =>
            create subtrees of height h-1 (full height subtree),
            and of height h-2 (short height subtree) recursively
            either tree can have perfect height subtrees or
            left short right full subtrees or
            left full right short subrees
     */

    def constructHeightBalancedBTs[T](v: T)(h: Int): List[Tree[T]] =
        if h <= 0 then List(EndNode)
        else if h == 1 then List(Node(v))
        else {
            val subTreesFull = constructHeightBalancedBTs(v)(h - 1)
            val subTreesShort = constructHeightBalancedBTs(v)(h - 2)
            val imperfectHeightBTs = for {
                subTrees1 <- subTreesFull
                subTrees2 <- subTreesShort
                combinedTree <- List(
                  Node(v, subTrees1, subTrees2),
                  Node(v, subTrees2, subTrees1)
                )
            } yield combinedTree

            val perfectHeightBTs = for {
                subTreeLeft <- subTreesFull
                subTreeRight <- subTreesFull
            } yield Node(v, subTreeLeft, subTreeRight)

            imperfectHeightBTs ::: perfectHeightBTs
        }

    /*
        P60
        construct height balanced trees with given number of nodes

        solution =>
            creating helping functions
            1. minHBalNodes => that returns minimum possible nodes given a height for height balanced tree
                as height balanced will have height -1 and height -2 at least in subtrees
                we call recursively to find min nodes and add them

            2. maxHBalNodes => max possible nodes in given height for hbalBt
            3. minHeightInHBal => given number of nodes tell min possible height for HbalBt
                (densely packed but still a height balanced binary tree)
            4. maxHeightInHBal => given nodes count tell max possible height for HbalBT
                (sparsely packed tree but satifying height conditions)
            5. countNodes
     */

    def minNodesInHBal(height: Int): Int =
        if height <= 0 then 0
        else if height == 1 then 1
        else minNodesInHBal(height - 1) + minNodesInHBal(height - 2) + 1

    @tailrec
    def maxNodeInHBal(height: Int, acc: Int = 1): Int =
        if height == 0 then acc - 1
        else maxNodeInHBal(height - 1, acc * 2)

    def minHeightInHBal(nodes: Int): Int =
        if nodes == 0 then 0
        else minHeightInHBal(nodes / 2) + 1

    def maxHeightInHBal(nodes: Int): Int =
        LazyList.from(1).takeWhile(minNodesInHBal(_) <= nodes).last

    def countNodes[T](root: Tree[T]): Int = root match
        case EndNode => 0
        case Node(_, leftSt, rightSt) =>
            1 + countNodes(leftSt) + countNodes(rightSt)

    // it constructs trees given nodes (not height)
    def constructHeightBalancedBTs_v2[T](v: T)(nodes: Int): List[Tree[T]] =
        for {
            _ <- List.empty // just to final container will be list and not sequence
            height <- minHeightInHBal(nodes) to maxHeightInHBal(nodes)
            hBalTree <- constructHeightBalancedBTs(v)(height)
            if hBalTree.countNodes == nodes
        } yield hBalTree

    /* 
        P61: count leaves of a Binary tree
        P61-A : collect leaves of a binary tree into a list
     */

    def countLeaf[T](root: Tree[T]): Int = root match
        case EndNode => 0
        case Node(_, EndNode, EndNode) => 1
        case Node(_, left, right) => countLeaf(left) + countLeaf(right)


    def collectLeaves[T](root: Tree[T]): List[T] = root match
        case EndNode => Nil
        case n @ Node(v, EndNode, EndNode) => List(v)
        case Node(_, left, right) => collectLeaves(left) ++ collectLeaves(right)


    /* 
        P62 collect internal nodes of a binary tree in a list
        P62B collect nodes at a given level
     */

    def collectInternalNodes[T](root: Tree[T]): List[T] = root match
        case EndNode => Nil
        case Node(_, EndNode, EndNode) => Nil
        case Node(v, left, right) => v:: collectInternalNodes(left) ::: collectInternalNodes(right)

    def collectNodesAtLevel[T](root: Tree[T], level: Int): List[T] = (level , root) match
        case (l, Node(v, left, right)) => 
            if l <= 0 then Nil
            else if l == 1 then List(v)
            else collectNodesAtLevel(left, l-1):::collectNodesAtLevel(right, l-1)
        case (_, EndNode) => Nil
    
}
object P55Demo extends App {
    // println(CreateBTsExercises.completelyBalancedBTs("x")(4))
    // println(constructHeightBalancedBTs("x")(3))

}
