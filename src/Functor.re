module type Functor = {
  type t('a); 
  let fmap: ('a => 'b, t('a)) => t('b);
};

module FunctorUtils = (F: Functor) => {
  open Base;
  include F;
  let (<$>) = (f, x) => fmap(f, x);
  let (<&>) = (x, f) => flip(fmap, x, f);
  let (<$) = (r, x) => fmap(const(r), x);
  let ($>) = (r, x) => flip((<$), r, x);
  let void = (f, x) => fmap(x => ignore(f(x)), x);
};

module FunctorLaws = (F: Functor) => {
  open Base;
  open F;
  let idLaw = x => fmap(id, x) == x;
  let composeLaw = (f, g, xs) => fmap(f <<< g, xs) == fmap(f, fmap(g, xs));
};

module ListF_: Functor with type t('a) = list('a) = {
  type t('a) = list('a);
  let fmap = f => List.map(f);
};

module ListFunctor = FunctorUtils(ListF_);

module OptionF_: Functor with type t('a) = option('a) = {
  type t('a) = option('a);
  let fmap = f =>
    fun
    | Some(x) => Some(f(x))
    | None => None;
};

module OptionFunctor = FunctorUtils(OptionF_);