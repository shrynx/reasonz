module type Extend = {
  type t('a);
  let extend: (t('a) => 'b, t('a)) => t('b);
};