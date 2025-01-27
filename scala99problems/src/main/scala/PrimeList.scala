// Parametric sieve method takes in first value and filter the tail based on that, recursively 
def sieve[T](lzList: LazyList[T]) (f: T => T => Boolean): LazyList[T] = { lzList match
    case e#::t => e #::sieve(t.filterNot(f(e)))(f)
    case _ => LazyList.empty[T]
}

val primes = sieve(LazyList.from(2))((a:Int) => (b: Int) => b%a == 0)

def main(args: Array[String]): Unit = {
    print(primes.take(100).toList)
}