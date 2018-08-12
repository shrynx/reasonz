module type Contravariant = {
  type t('a);
  let contramap: ('a => 'b, t('b)) => t('a);
};