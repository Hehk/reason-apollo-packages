open ReasonApolloClient;

[@bs.module "react-apollo"]
external graphql :
  ReasonApolloClient.ApolloClient.documentNode =>
  [@bs] (ReasonReact.reactClass => ReasonReact.reactClass) =
  "";

type apolloResponse('a) = {
  loading: bool,
  variables: Js.Json.t,
  error: option(ApolloClient.graphqlError),
  result: option('a)
};

external castResponse : Js.t({..}) => Js.Json.t = "%identity";

[@bs.module] external gql : [@bs] (string => ApolloClient.documentNode) = "graphql-tag";

let make = (~query, ~parse=?, ~component, ~make, ()) => {
  let graphqlWrapper = graphql([@bs] gql(query));
  let jsComponent =
    ReasonReact.wrapReasonForJs(
      ~component,
      props => {
        let loading = Js.to_bool(props##data##loading);
        let result =
          if (loading) {
            None;
          } else {
            /* Switch if you want to use a different parsing function other than
               the default apollo one*/
            Some(
              switch parse {
              | None => Obj.magic(props##data)
              | Some(f) => f(castResponse(props##data))
              }
            );
          };
        let data = {
          variables: props##variables,
          error: Js.Nullable.toOption(props##error),
          loading,
          result
        };
        make(~data, [||]);
      }
    );
  let reactClass = [@bs] graphqlWrapper(jsComponent);
  (children: array(ReasonReact.reactElement)) =>
    ReasonReact.wrapJsForReason(~reactClass, ~props=Js.Obj.empty(), children);
};
