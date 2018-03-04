open ReasonApolloClient;

[@bs.module "apollo-cache-inmemory"] [@bs.new] external _make : unit => ApolloCache.t = "InMemoryCache";

let make = () => _make();
