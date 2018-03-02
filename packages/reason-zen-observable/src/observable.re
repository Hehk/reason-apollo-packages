type t('a);

type observableLike('a);

module Subscription = {
  type t;
  [@bs.send.pipe : t] external closed : bool = "";
  [@bs.send.pipe : t] external unsubscribe : unit => unit = "";
};

/* module Observer = { */
/*   type t('a); */
/*   [@bs.send.pipe : t('a)] external start : Js.Nullable.t(Subscription.t => 'b) = ""; */
/*   [@bs.send.pipe : t('a)] external next : Js.Nullable.t('a => unit) = ""; */
/*   [@bs.send.pipe : t('a)] external error : Js.Nullable.t('b => unit) = ""; */
/*   [@bs.send.pipe : t('a)] external complete : Js.Nullable.t(unit => unit) = ""; */
/* }; */

module SubscriptionObserver = {
  type t('a);
  [@bs.send.pipe : t('a)] external closed : bool = "";
  [@bs.send.pipe : t('a)] external next : 'a => unit = "";
  [@bs.send.pipe : t('a)] external error : 'b => unit = "";
  [@bs.send.pipe : t('a)] external complete : unit => unit = "";
};

/* Making a new observable */
[@bs.module] [@bs.new] external _make : ((SubscriptionObserver.t('a), unit) => unit) => t('a) = "zen-observable";

let make = f => _make(f);

/* Functions that coerce to the observable type */
[@bs.module "zen-observable"] external _of_observable : t('a) => t('a) = "from";

[@bs.module "zen-observable"] external _of_observable_like : observableLike('a) => t('a) = "from";

[@bs.module "zen-observable"] external _of_array : array('a) => t('a) = "from";

let of_observable = x => _of_observable(x);

let of_observable_like = x => _of_observable_like(x);

let of_array = x => _of_array(x);

let of_list = x => x |> Array.of_list |> _of_array;

/* Functions on the observable */
[@bs.send.pipe : t('a)] external subscribe : ('a => unit, 'b => unit, unit => unit) => Subscription.t = "";

[@bs.send.pipe : t('a)] external forEach : ('a => unit) => Js.Promise.t(unit) = "";

[@bs.send.pipe : t('a)] external map : ('a => 'b) => t('b) = "";

[@bs.send.pipe : t('a)] external filter : ('a => bool) => t('a) = "";

[@bs.send.pipe : t('a)] external reduce : (('b, 'a) => 'b, 'b) => t('b) = "";

[@bs.send.pipe : t('a)] external flatMap : ('a => observableLike('b)) => t('b) = "";
