open ReasonReactApollo;

let app =
  <ApolloProvider client=Apollo.client>
    <Page />
  </ApolloProvider>;

ReactDOMRe.renderToElementWithId(app, "index");
