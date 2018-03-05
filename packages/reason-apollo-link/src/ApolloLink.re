open ReasonZenObservable;

type t;

type fetchResult;

type nextLink = Operation.t => Observable.t(fetchResult);

type requestHandler = (Operation.t, Js.Nullable.t(nextLink)) => Js.Nullable.t(Observable.t(fetchResult));

[@bs.module "apollo-link"] [@bs.new] external _make : requestHandler => t = "ApolloLink";

/* Allow for link code to deal with options rather than the nullable system */
let make = handler =>
  _make((operation, forward) =>
    Js.Nullable.fromOption(handler(~operation, ~forward=Js.Nullable.toOption(forward), ()))
  );

[@bs.module "apollo-link"] external from : array(t) => t = "";

let from = from;

let fromList = x => x |> Array.of_list |> from;

[@bs.module "apollo-link"] external concat : (t, t) => t = "";

let concat = concat;

[@bs.module "apollo-link"] [@bs.scope "ApolloLink"] external split : (Operation.t => bool, t, t) => t = "";

let split = (~test, a, b) => split(test, a, b);
