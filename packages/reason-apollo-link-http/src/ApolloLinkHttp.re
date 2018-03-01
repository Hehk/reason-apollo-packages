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

[@bs.module "apollo-link-http"]
external _make : options => ApolloLink.t = "createHttpLink";

let make =
    (
      ~uri=?,
      ~includeExtensions=?,
      ~fetch=?,
      ~header=?,
      ~credentials=?,
      ~fetchOptions=?,
      ()
    ) =>
  _make({
    "uri": Js.Nullable.from_opt(uri),
    "includeExtensions": Js.Nullable.from_opt(includeExtensions),
    "fetch": Js.Nullable.from_opt(fetch),
    "headers": Js.Nullable.from_opt(header),
    "credentials": Js.Nullable.from_opt(credentials),
    "fetchOptions": Js.Nullable.from_opt(fetchOptions)
  });
