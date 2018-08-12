module type BiFunctor = {
  type t('a, 'b);
  let bimap: ('a => 'b, 'c => 'd, t('a, 'c)) => t('b, 'd);
};