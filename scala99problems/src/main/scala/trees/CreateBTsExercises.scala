/*
    P55 (**) Construct completely balanced binary trees.
    this is an exercise to create a balanced binary tree given the number of nodes
    give all possible solutions
 */
import CreateBTsExercises.constructHeightBalancedBTs

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
            val subTreesFull = constructHeightBalancedBTs(v)(h-1)
            val subTreesShort = constructHeightBalancedBTs(v)(h-2)
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

            imperfectHeightBTs:::perfectHeightBTs
        }

    /* 
        P60
        construct height balanced trees with given number of nodes 
    
     */
    
}
object P55Demo extends App {
    // println(CreateBTsExercises.completelyBalancedBTs("x")(4))
    println(constructHeightBalancedBTs("x")(3))
}
