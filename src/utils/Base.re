/* 
  identity function
  id :: a -> a
 */
let id = (x) => x;

/* 
  dollar function
  ($) :: (a -> b) -> a -> b
 */
let ($) = (f,x) => f(x);

/* 
  flip function
  flip :: (a -> b -> c) -> b -> a -> c
 */
let flip = (f,x,y) => f(y,x);

/* 
  const function
  const :: a -> b -> a
 */
let const = (x,_) => x;

/* 
  compose function
  (<<<) :: (b -> c) -> (a -> b) -> a -> c
 */
let (<<<) = (f, g, x) => f(g(x));

/* 
  flip compose function
  (>>>) :: (a -> b) -> (b -> c) -> a -> c
 */
let (>>>) = (f, g, x) => g(f(x));
