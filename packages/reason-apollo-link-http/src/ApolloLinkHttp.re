open ReasonApolloLink;

type fetch;

type options = {
  .
  "uri": Js.Nullable.t(string),
  "includeExtensions": Js.Nullable.t(Js.boolean),
  "fetch": Js.Nullable.t(fetch),
  "headers": Js.Nullable.t(Js.Json.t),
  "credentials": Js.Nullable.t(string),
  "fetchOptions": Js.Nullable.t(Js.Json.t)
};

[@bs.module "apollo-link-http"] external _make : options => ApolloLink.t = "createHttpLink";

let make = (~uri=?, ~includeExtensions=?, ~fetch=?, ~header=?, ~credentials=?, ~fetchOptions=?, ()) =>
  _make({
    "uri": Js.Nullable.fromOption(uri),
    "includeExtensions": Js.Nullable.fromOption(includeExtensions),
    "fetch": Js.Nullable.fromOption(fetch),
    "headers": Js.Nullable.fromOption(header),
    "credentials": Js.Nullable.fromOption(credentials),
    "fetchOptions": Js.Nullable.fromOption(fetchOptions)
  });
