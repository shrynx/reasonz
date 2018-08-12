open Base;

let f = x => x + 1;

let g = x => x * 2;

let h = x => x / 5;

let x = Functor.OptionFunctor.(f <$> Some(5));

let y = Applicative.ListApplicative.([f, g, h] <*> [1, 2, 3, 4, 5]);

let z = {
  open Monad.ListMonad;
  let repeat = x => [x, x];
  repeat =<< [1, 2, 3, 4, 5];
};

module TLO = Traverseable.ListTraversable(Applicative.OptionApplicative);

let listOfOption = [Some(5), Some(6), Some(7)];

let optionList = TLO.(traverse(id, listOfOption));