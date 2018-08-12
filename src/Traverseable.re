open Applicative;

module type Traversable = {
  type t('a);
  module Applicative: Applicative;
  let traverse: ('a => Applicative.t('b), t('a)) => Applicative.t(t('b));
};

module ListTraversable =
       (A: Applicative)
       : (
           Traversable with
             type t('a) = list('a) and type Applicative.t('a) = A.t('a)
         ) => {
  type t('a) = list('a);
  module Applicative = A;
  module AppU = ApplicativeUtils(Applicative);
  open AppU;
  let rec traverse = (f, xs) =>
    switch (xs) {
    | [] => A.pure([])
    | [x, ...xs] => ((y, ys) => [y, ...ys]) <$> f(x) <*> traverse(f, xs)
    };
};

module OptionTraversable =
       (A: Applicative)
       : (
           Traversable with
             type t('a) = option('a) and type Applicative.t('a) = A.t('a)
         ) => {
  type t('a) = option('a);
  module Applicative = A;
  module AppU = ApplicativeUtils(Applicative);
  open AppU;
  let traverse = (f, x) =>
    switch (x) {
    | None => A.pure(None)
    | Some(x) => (a => Some(a)) <$> f(x)
    };
};