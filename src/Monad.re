module type Monad = {
  open Applicative;
  type t('a);
  include Applicative with type t('a) := t('a);
  let bind: (t('a), 'a => t('b)) => t('b);
};

module MonadUtils = (M: Monad) => {
  open Base;
  include M;
  module AppU = Applicative.ApplicativeUtils(M);
  include (AppU :(module type of AppU) with type t('a) := AppU.t('a));
  
  let return = pure;
  let (>>=) = bind;
  let (=<<) = (f, m) => flip(bind, f, m);
  let join = m => id =<< m;
  let (>>) = (m, k) => m >>= const(k);
  let (<<) = (m,k) => flip((>>), m, k);
  let (>=>) = (f, g, x) => f(x) >>= g;
  let (<=<) = (f, g, x) => f =<< g(x);
};

module MonadLaws = (M: Monad) => {
  module MonadU = MonadUtils(M);
  open MonadU;
  let leftIdLaw = (f, x) => return(x) >>= f == f(x);
  let rightIdLaw = x => x >>= return == x;
  let associativityLaw = (m, f, g) =>
    m >>= (x => f(x) >>= g) == (m >>= f >>= g);
};

module ListM_: Monad with type t('a) = list('a) = {
  include Applicative.ListApplicative;
  let bind = (m, f) =>
    List.fold_right((x, y) => List.append(f(x), y), m, []);
};

module ListMonad = MonadUtils(ListM_);

module OptionM_: Monad with type t('a) = option('a) = {
  include Applicative.OptionApplicative;
  let bind = (m, f) =>
    switch (m) {
    | None => None
    | Some(x) => f(x)
    };
};
module OptionMonad = MonadUtils(OptionM_);