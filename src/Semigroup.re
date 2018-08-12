module type Semigroup = {type t; let append: (t, t) => t;};

module StringSemigroup: Semigroup with type t = string = {
  type t = string;
  let append = (++);
};

module type GenericTypeConstuctor = {type t;};

module ListSemigroup =
       (T: GenericTypeConstuctor)
       : (Semigroup with type t = list(T.t)) => {
  type t = list(T.t);
  let append = (@);
};