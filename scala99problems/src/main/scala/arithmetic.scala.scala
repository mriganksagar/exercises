import scala.math.Numeric.Implicits._
import scala.math.Ordering.Implicits._

object ArithmeticUtilities {
  // finding primes
  val primes = {
    def sieve(l: LazyList[Int]): LazyList[Int] = {
      l.head #:: sieve(l.tail.filter(_ % l.head != 0))
    }
    sieve(LazyList.from(2))
  }

  // fixed point function
  def fixedPoint[T: Numeric](f: T => T, x: T, tolerance: T): T = {
    val next = f(x)
    if ((next - x).abs <= tolerance) then next
    else fixedPoint(f, next, tolerance)
  }

}

object ArithmeticQuestions {
  import ArithmeticUtilities._

  // p31 an integer is prime or not
  def isPrime(number: Int): Boolean =
    primes.takeWhile(_ <= number).contains(number)

  // alternatively, by checking only primes till root of number and then divisibility
  def isPrime_efficient(n: Int): Boolean = if n < 2 then false
  else primes takeWhile { _ <= Math.sqrt(n) } forall { e => n % e != 0 }

  // p32 greatest common divisor of two positive integers
  def findGreatestCommonDivisor(a: Int, b: Int): Int =
    if a > b then findGreatestCommonDivisor(b, a)
    else if a == 0 then b
    else findGreatestCommonDivisor(b % a, a)

  // p33 find if two positive integers are coprime
  def findCoPrime(a: Int, b: Int): Boolean =
    findGreatestCommonDivisor(a, b) == 1

  // p34 eulers totient function
  def findEulersTotientFunction(a: Int) = 
    (2 until a).count( e => findCoPrime(a, e))


  // p35 find prime factors of a number
  def findPrimeFactors(n: Int): List[Int] = {
    def findprimelist(i: Int, acc: List[Int], nextPrimes: LazyList[Int]): List[Int] = {
        if i == 1 then acc.reverse
        else if i % nextPrimes.head == 0 then findprimelist(i/nextPrimes.head, nextPrimes.head::acc, nextPrimes)
        else findprimelist(i, acc, nextPrimes.tail) 
    }

    findprimelist(n, Nil, primes)
  }

  // p36 determine prime factors with multiplicity
  // i can modify p35 a little or use encoding run length from list questions
  def findPrimeFactorsWithMultiplicity(n: Int): List[(Int, Int)] = {
    def formatWithMultiplicity[T](l:List[T], acc: List[(T, Int)]): List[(T, Int)] = {
      if l == Nil then acc.reverse
      else {
        val (first, last) = l.span(_==l.head)
        formatWithMultiplicity(last, (first.head, first.size)::acc)
      }
    }

    formatWithMultiplicity(findPrimeFactors(n), Nil)
  }
  
}

object TestArithmeticQuestions extends App {
  import ArithmeticQuestions._
  import ArithmeticUtilities._

  // test is prime numbers
  def testIsPrimeNumber(): Unit = {
    println(primes.take(100).toList)
    println(isPrime(541))
    println(isPrime(531))
  }

  // test g c f
  def testFindGreatestCommonDivisor(): Unit = {
    println(findGreatestCommonDivisor(13, 12))
    println(findGreatestCommonDivisor(134, 67))
    println(findGreatestCommonDivisor(123, 123))
  }

  // test is two numbers co prime    
  def testFindCoPrime(): Unit = {
    println(findCoPrime(5, 50))
    println(findCoPrime(51, 50))
  }

  // test prime factors
  def testFindPrimeFactors():Unit = {
    println(findPrimeFactors(315))
    println(findPrimeFactors(133))
  }

  // test prime factors with Multiplicity
  def testFindPrimeFactorsWithMultiplicity(): Unit = {
    println(findPrimeFactorsWithMultiplicity(315))
    println(findPrimeFactorsWithMultiplicity(133))
  }
  
  // testIsPrimeNumber()
  // testFindGreatestCommonDivisor()
  // testFindCoPrime()
  // testFindPrimeFactors()
  // testFindPrimeFactorsWithMultiplicity()
}
