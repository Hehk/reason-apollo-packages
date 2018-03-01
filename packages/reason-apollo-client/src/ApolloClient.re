type t;

type clientOptions = {
  .
  "link": ApolloLink.t,
  "cache": ApolloCache.t,
  "ssrMode": Js.boolean,
  "ssrForceFetchDelay": int,
  "connectToDevTools": Js.Nullable.t(Js.boolean),
  "queryDeduplication": Js.boolean
};

[@bs.module "apollo-client"] [@bs.new] external _make : clientOptions => t = "ApolloClient";

let make = (~link, ~cache, ~ssrMode=false, ~ssrForceFetchDelay=0, ~connectToDevTools=?, ~queryDeduplication=true, ()) =>
  _make({
    "link": link,
    "cache": cache,
    "ssrMode": Js.Boolean.to_js_boolean(ssrMode),
    "ssrForceFetchDelay": ssrForceFetchDelay,
    "connectToDevTools": Js.Nullable.from_opt(connectToDevTools),
    "queryDeduplication": Js.Boolean.to_js_boolean(queryDeduplication)
  });

/* The base public functions on an apollo client */
[@bs.send.pipe : t] external watchQuery : unit => unit = "";

[@bs.send.pipe : t] external query : unit => unit = "";

[@bs.send.pipe : t] external mutate : unit => unit = "";

[@bs.send.pipe : t] external subscribe : unit => unit = "";

[@bs.send.pipe : t] external readQuery : unit => unit = "";

[@bs.send.pipe : t] external readFragment : unit => unit = "";

[@bs.send.pipe : t] external writeQuery : unit => unit = "";

[@bs.send.pipe : t] external writeFragment : unit => unit = "";

[@bs.send.pipe : t] external writeData : unit => unit = "";

[@bs.send.pipe : t] external initQueryManager : unit => unit = "";

[@bs.send.pipe : t] external resetStore : unit => unit = "";

[@bs.send.pipe : t] external onResetStore : unit => unit = "";

[@bs.send.pipe : t] external reFetchObservableQuery : unit => unit = "";

[@bs.send.pipe : t] external extract : unit => unit = "";

[@bs.send.pipe : t] external restore : unit => unit = "";
