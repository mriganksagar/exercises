import scala.annotation.tailrec
object ListQuestions {
  def lastElementOfList[T](l: List[T]): Option[T] = {
    l match
      case Nil      => None
      case e :: Nil => Some(e)
      case _ :: ls  => lastElementOfList(ls)
  }

  def secondLastElement[T](l: List[T]): Option[T] = l match
    case _ :: e :: Nil => Some(e)
    case _ :: _ :: ls  => lastElementOfList(ls)
    case _             => None

  def findKthElementOfList[T](l: List[T], k: Int): Option[T] = {
    l match
      case e :: ls if k == 1 => Some(e)
      case _ :: ls if k > 1  => findKthElementOfList(ls, k - 1)
      case _                 => None
  }

  // count elements in a list
  def countElementsInList[T](l: List[T]) = {
    def helperCount2(list: List[T], count: Int): Int = list match
      case _ :: xs => helperCount2(xs, count + 1)
      case Nil     => count

    def helperCount(list: List[T], count: Int): Int =
      if list == Nil then count
      else helperCount(list.tail, count + 1)

    helperCount2(l, 0)
  }

  // reverse a list
  def reverseAList[T](l: List[T]): List[T] = {
    def helper(list: List[T], acc: List[T]): List[T] = list match
      case x :: xs => helper(xs, x :: acc)
      case Nil     => acc

    helper(l, Nil)
  }

  // is Palindrome
  def isPalindrome[T](l: List[T]): Boolean = {
    val reversedL = reverseAList(l)

    def areTwoListsSame(a: List[T], b: List[T]): Boolean =
      (a, b) match
        case (Nil, Nil)                   => true
        case (a :: as, b :: bs) if a == b => areTwoListsSame(as, bs)
        case _                            => false

    areTwoListsSame(l, reversedL)
  }

  /// creating a custom my Flatmap function (just a homegrown collection )
  def myFlatmap[T](l: List[T])(f: T => List[T]) = {
    def prepend(current: List[T], add: List[T]): List[T] = add match
      case head :: next => prepend(head :: current, next)
      case Nil          => current

    def helper(list: List[T], acc: List[T]): List[T] = list match
      case x :: xs => helper(xs, prepend(acc, f(x)))
      case Nil     => acc.reverse

    helper(l, Nil)
  }

  // given a list containing nested lists, flatten it all
  def flattenNestedList(list: List[Any]): List[Any] = myFlatmap(list) {
    case e: List[_] => flattenNestedList(e)
    case e          => List(e)
  }

  // eliminate consecutive duplicate elements
  def elimiateConsecutiveDuplicates[T](l: List[T]): List[T] = l match
    case e1 :: e2 :: tail if e1 == e2 =>
      elimiateConsecutiveDuplicates(e2 :: tail)
    case e1 :: e2 :: tail => e1 :: elimiateConsecutiveDuplicates(e2 :: tail)
    case ls               => ls

  // pack consecutive duplicate elements of list into sublists
  def packConsecutiveDuplicatesIntoList[T](l:List[T]): List[List[T]] = {
    @tailrec
    def helper(list:List[T], acc: List[List[T]]): List[List[T]] = (list, acc) match
      case (elem::tail, (a::as)::ass) if elem == a => helper(tail, (elem::a::as)::ass) 
      case (elem::tail, _) => helper(tail, List(elem)::acc)
      case (Nil, _) => acc.reverse
    
    helper(l, Nil)
  }

  //P 10 run length encoding of a list return list(a,a,b) as list((2,a), (1,b))
  def runLengthEncodingOfList[T](list:List[T]): List[(Int, T)] = {
    val packedList = packConsecutiveDuplicatesIntoList(list)
    packedList.map(e => (e.length, e.head))
  }

  // p11 modified run length encoding return list (a,a,b) as list((2,a), b)
  def modifiedRunLengthEncoding[T](list:List[T]): List[T | (Int, T)] = {
    val packedList = packConsecutiveDuplicatesIntoList(list)
    packedList.map{ sl => sl match
      case e:: Nil => e
      case e::es => (sl.length, e)
    }
  }
}

object TestListQuestions extends App {
  import ListQuestions._
  // test last Element
  def test1(): Unit = {
    println(lastElementOfList(List(1, 3, 2, 6, 3)))
    println(lastElementOfList(List.empty[Int]))
  }

  // test second last element
  def test2(): Unit = {
    println(secondLastElement(List(1, 3)))
    println(secondLastElement(List(1)))
    println(secondLastElement(List(1, 3, 5)))
    println(secondLastElement(List.empty[Int]))
  }
  // test kth element

  def test3(): Unit = {
    println(findKthElementOfList(List(1, 2, 4, 5, 6, 7), 3))
    println(findKthElementOfList(List(1, 2, 4, 5, 6, 7), 6))
    println(findKthElementOfList(List(1, 2, 4, 5, 6, 7), 7))
    println(findKthElementOfList(List.empty[Int], 1))
  }

  // test counting elements in list
  def test4(): Unit = {
    println(countElementsInList(List(1, 2, 4, 5)))
    println(countElementsInList(List.empty[Int]))
  }

  // reverse a list
  def testReverseList(): Unit = {
    println(reverseAList(List(1, 2, 4, 6, 7)))
    println(reverseAList(List.empty[Int]))
  }

  // check palindrome
  def testPalindrome(): Unit = {
    println(isPalindrome(List(1, 2, 3, 2, 1)))
    println(isPalindrome(List(1, 2, 3, 2, 1, 1)))
    println(isPalindrome(List.empty[Int]))
  }

  // check flattening list
  def testFlatteningList(): Unit = {
    println(
      flattenNestedList(
        List(
          List(1, 2, 3),
          4,
          List(13, 14, 15, List(30, 40, List(411))),
          List.empty
        )
      )
    )
  }

  // check eliminate consecutive duplicates
  def testEliminateConsecutiveDuplicates(): Unit = {
    println(
      elimiateConsecutiveDuplicates(List(1, 1, 1, 2, 2, 3, 4, 5, 6, 6, 5))
    )
  }

  // check pack consecutive duplicate elements
  def testPackConsecutiveDuplicateElementsIntoList():Unit = {
    println(packConsecutiveDuplicatesIntoList(List(1,2,2,3,4,4,4,4,5,6)))
    println(packConsecutiveDuplicatesIntoList(List.empty[Int]))
  }

  // check modified run length encoding
  def testModifiedRunLengthEncoding():Unit = {
    println(modifiedRunLengthEncoding(List(1,3,4,4,4,5,5,6)))
    println(modifiedRunLengthEncoding(List.empty[Int]))
  }

  
}
