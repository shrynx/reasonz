module type Monoid = {
  type t;
  open Semigroup;
  include Semigroup with type t := t;
  let empty: t;
};

module MonoidUtils = (M: Monoid) => {
  include M;
  let (<+>) = (x, y) => append(x, y);
  let concat = xs => List.fold_left((<+>), empty, xs);
};

module StringM_: Monoid with type t = string = {
  include Semigroup.StringSemigroup;
  let empty = "";
};

module StringMonoid = MonoidUtils(StringM_);

module type GenericTypeConstuctor = {type t;};

module ListM_ = (T: GenericTypeConstuctor) : (Monoid with type t = list(T.t)) => {
  include
    Semigroup.ListSemigroup(
      {
        type t = T.t;
      },
    );
  let empty = [];
};

module ListMonoid = (T: GenericTypeConstuctor) =>
  MonoidUtils(
    (
      ListM_(
        {
          type t = T.t;
        },
      )
    ),
  );