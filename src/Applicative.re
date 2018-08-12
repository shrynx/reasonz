module type Applicative = {
  open Functor;
  type t('a);
  include Functor with type t('a) := t('a);
  let pure: 'a => t('a);
  let ap: (t('a => 'b), t('a)) => t('b);
};

module ApplicativeUtils = (A: Applicative) => {
  open Base;
  include A;
  module FunU = Functor.FunctorUtils(A);
  include (FunU:(module type of FunU) with type t('a) := FunU.t('a)); 

  let (<*>) = f => ap(f);
  let liftA = (f, x) => f <$> x;
  let liftA2 = (f, x, y) => f <$> x <*> y;
  let liftA3 = (f, x, y, z) => f <$> x <*> y <*> z;
  let ( <* ) = (r, x) => const <$> r <*> x;
};

module ApplicativeLaws = (A: Applicative) => {
  open Base;
  module AppU = ApplicativeUtils(A);
  open AppU;
  let idLaw = x => pure(id) <*> x == x;
  let homomorphismLaw = (f, x) => pure(f) <*> pure(x) == pure(f(x));
  let interchangeLaw = (u, y) => u <*> pure(y) == (pure(f => f(y)) <*> u);
  let compositionLaw = (u, v, w) =>
    pure((<<<)) <*> u <*> v <*> w == (u <*> (v <*> w));
};

module ListA_: Applicative with type t('a) = list('a) = {
  include Functor.ListFunctor;
  let pure = x => [x];
  let ap = (fs, xs) => fmap(f => fmap(x => f(x), xs), fs) |> List.concat;
};

module ListApplicative = ApplicativeUtils(ListA_);

module OptionA_: Applicative with type t('a) = option('a) = {
  include Functor.OptionFunctor;
  let pure = x => Some(x);
  let ap = (f, x) =>
    switch (f, x) {
    | (Some(f), Some(x)) => Some(f(x))
    | _ => None
    };
};

module OptionApplicative = ApplicativeUtils(OptionA_);