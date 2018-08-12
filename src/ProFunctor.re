module type ProFunctor = {
  type t('a, 'b);
  let dimap: ('a => 'b, 'c => 'd, t('b, 'c)) => t('a, 'd);
};

module ProFunctorUtils = (P: ProFunctor) => {
  open Base;
  include P;
  let lmap = f => dimap(f, id);
  let rmap = f => dimap(id, f);
};