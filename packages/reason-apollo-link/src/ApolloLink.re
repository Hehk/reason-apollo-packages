open ReasonZenObservable;

type t; 

module Operation = {
  type t = {
    .
    "query": Js.Json.t,
    "variables": Js.Json.t,
    "opeationName": Js.Nullable.t(string),
    "extensions": Js.Json.t
  };
  [@bs.send.pipe : t] external getContext : Js.t({..}) = "";
  [@bs.send.pipe : t] external setContext : (Js.t({..}) => Js.t({..})) => unit = "";
  [@bs.send.pipe : t] external toKey : unit => string = "";
};

type operation = {
  .
  "query": Js.Json.t,
  "variables": Js.Json.t,
  "operationName": Js.Nullable.t(string),
  "extensions": Js.Json.t
};

type fetchResult;

type nextLink = Operation.t => Observable.t(fetchResult);

type requestHandler =
  (Operation.t, Js.Nullable.t(nextLink)) => Js.Nullable.t(Observable.t(fetchResult));

[@bs.module "apollo-link"] [@bs.new] external _make : requestHandler => t = "ApolloLink";

/* Allow for link code to deal with options rather than the nullable system */
let make = handler =>
  _make((operation, forward) =>
    Js.Nullable.fromOption(handler(operation, Js.Nullable.toOption(forward)))
  );

[@bs.module "apollo-link"] external from : array(t) => t = "";

let from = from;

let fromList = x => x |> Array.of_list |> from;

[@bs.module "apollo-link"] external concat : (t, t) => t = "";

let concat = concat;

[@bs.module "apollo-link"] [@bs.scope "ApolloLink"]
external split : (Operation.t => bool, t, t) => t = "";
