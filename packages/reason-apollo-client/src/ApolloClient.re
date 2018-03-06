open ReasonApolloLink;

open ReasonZenObservable;

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

let make =
    (
      ~link,
      ~cache,
      ~ssrMode=false,
      ~ssrForceFetchDelay=0,
      ~connectToDevTools=?,
      ~queryDeduplication=true,
      ()
    ) =>
  _make({
    "link": link,
    "cache": cache,
    "ssrMode": Js.Boolean.to_js_boolean(ssrMode),
    "ssrForceFetchDelay": ssrForceFetchDelay,
    "connectToDevTools": Js.Nullable.fromOption(connectToDevTools),
    "queryDeduplication": Js.Boolean.to_js_boolean(queryDeduplication)
  });

type graphqlError;

type networkStatus;

type queryResults('a) = {
  .
  "data": 'a,
  "errors": Js.Nullable.t(graphqlError),
  "loading": Js.boolean,
  "networkStatus": networkStatus,
  "stale": Js.boolean
};

type queryString;

type fetchPolicy;

type errorPolicy;

type watchQueryOptions = {
  .
  "query": queryString,
  "variables": Js.Nullable.t(Js.Json.t),
  "pollInterval": Js.Nullable.t(int),
  "fetchPolicy": Js.Nullable.t(fetchPolicy),
  "errorPolicy": Js.Nullable.t(errorPolicy),
  "fetchResults": Js.Nullable.t(bool)
};

let addWatchQueryNamedArguments =
    (
      f,
      ~query,
      ~variables=?,
      ~pollInterval=?,
      ~fetchPolicy=?,
      ~errorPolicy=?,
      ~fetchResults=?,
      client
    ) =>
  f(
    Js.Nullable.(
      {
        "query": query,
        "variables": fromOption(variables),
        "pollInterval": fromOption(pollInterval),
        "fetchPolicy": fromOption(fetchPolicy),
        "errorPolicy": fromOption(errorPolicy),
        "fetchResults": fromOption(fetchResults)
      }
    ),
    client
  );


/* The base public functions on an apollo client */
[@bs.send.pipe : t]
external query : watchQueryOptions => Js.Promise.t(queryResults('a)) = "";

let query = addWatchQueryNamedArguments(query);

[@bs.send.pipe : t] external watchQuery : watchQueryOptions => Observable.t(Js.Json.t) = "";

let watchQuery = addWatchQueryNamedArguments(watchQuery);

/* TODO: All functions after this point are just boilerplate, none will work */
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
