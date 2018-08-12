module type Comonad = {
  open Extend;
  type t('a);
  include Extend with type t('a) := t('a);
  let extract: t('a) => 'a;
};