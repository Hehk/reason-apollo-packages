type t = {
  .
  "query": Js.Json.t,
  "variables": Js.Json.t,
  "opeationName": Js.Nullable.t(string),
  "extensions": Js.Json.t
};

[@bs.send.pipe : t] external getContext : Js.t({..}) = "";

[@bs.send.pipe : t]
external setContext : (Js.t({..}) => Js.t({..})) => unit = "";

[@bs.send.pipe : t] external toKey : unit => string = "";
