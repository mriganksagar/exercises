package homegrownDatastructures

import scala.annotation.tailrec

// P70 (**) Tree construction from a node string
case class MTree[+T](value: T, children: List[MTree[T]] = Nil){
    override def toString(): String = s"$value {${children.mkString(",")}}"

    def countNodes: Int = 1 + children.map(_.countNodes).sum


    // returns pair - (internalpathlength, nodescount)
    private def internalPathLengthAux: (Int, Int) = 
        children.view.map(_.internalPathLengthAux).map(p => (p._1 + p._2 ) -> p._2).fold((0, 1))((a, b) => (a._1 + b._1, a._2 + b._2))       
    

    def internalPathLength: Int = this.internalPathLengthAux._1

    def postOrder: List[T] = {
        children.map(_.postOrder).foldRight(Nil)(_:::_).appended(value)
    }
}

object MTree{
    private def createMTreeAux(s: String): (MTree[Char], String) = {
        def mSubtrees(s: String): (List[MTree[Char]], String) = {
            if s(0) == '^' then Nil -> s.drop(1)
            else {
                val (firstChild, restString) = createMTreeAux(s)
                val rest = mSubtrees(restString)
                (firstChild:: rest._1) -> rest._2 
            }
        }

        @tailrec
        def mSubtreesTail(s: String, acc: List[MTree[Char]] = Nil): (List[MTree[Char]], String) = {
            if s(0) == '^' then acc.reverse -> s.drop(1)
            else {
                val (child, restString) = createMTreeAux(s)
                mSubtreesTail(restString, child::acc)
            }
        }

        val rest = mSubtreesTail(s.drop(1))
        MTree(s(0), rest._1) -> rest._2
    }

    def createMTree(s:String): MTree[Char] = createMTreeAux(s)._1

    given stringToMTree: Conversion[String, MTree[Char]] = s => createMTree(s)
}

object DemoMTree extends App {
    val a = MTree( 0, List(MTree(1, List(MTree(3), MTree(4)))))
    println(a.countNodes)
    println(a)

    val mtree1 = MTree.createMTree("afg^^c^bd^e^^^")
    println(mtree1.toString())
    println(mtree1.internalPathLength)

    import MTree.given
    println(
        "afg^^c^bd^e^^^".postOrder
    )
}
