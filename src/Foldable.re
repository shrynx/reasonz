module type Foldable = {
  type t('a);
  let foldmap: ('a => 'b, t('a)) => t('b);
};