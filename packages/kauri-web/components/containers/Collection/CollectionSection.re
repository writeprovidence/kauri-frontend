[@bs.module "../../../routes"]
external linkComponent: Link.linkComponent = "Link";

[@bs.deriving abstract]
type owner = {
  name: Js.Nullable.t(string),
  username: Js.Nullable.t(string),
  avatar: Js.Nullable.t(string),
  [@bs.as "id"]
  ownerId: string,
};

[@bs.deriving abstract]
type article = {
  attributes: Js.Nullable.t({. "background": Js.Nullable.t(string)}),
  id: string,
  datePublished: string,
  title: string,
  content: string,
  imageURL: Js.Nullable.t(string),
  owner,
  profileImage: Js.Nullable.t(string),
  version: int,
};

module Styles = {
  let container =
    Css.(
      style([
        display(`flex),
        flexDirection(column),
        width(`percent(100.0)),
        textAlign(center),
      ])
    );

  let section =
    Css.(
      style([
        display(`flex),
        width(`percent(100.0)),
        flexDirection(row),
        justifyContent(center),
        flexWrap(`wrap),
        selector("> div", [margin(px(15))]),
      ])
    );
};

let component = ReasonReact.statelessComponent("CollectionSection");

let make = (~name, ~description="", ~articles, _children) => {
  ...component,
  render: _self =>
    switch (articles) {
    | None => ReasonReact.null
    | Some(articles) =>
      <div className=Styles.container>
        <Paragraph text=name size=22 />
        <Paragraph text=description />
        <div className=Styles.section>
          {
            Js.Array.map(
              article => {
                let (articleId, articleVersion) =
                  article->(idGet, versionGet);

                <ArticleCard
                  key=article->idGet
                  id=articleId
                  version=articleVersion
                  /* Js.Nullable.t({. "background": Js.Nullable.t(string)}), */
                  imageURL={
                    switch (article->attributesGet->Js.Nullable.toOption) {
                    | Some(attributes) =>
                      switch (Js.Nullable.toOption(attributes##background)) {
                      | Some(background) => Some(background)
                      | None => None
                      }
                    | None => None
                    }
                  }
                  linkComponent={
                    (childrenProps, route) =>
                      <Link
                        useAnchorTag=true
                        linkComponent
                        toSlug={
                          route |> Js.String.includes("article") ?
                            Js.Nullable.return(article->titleGet) :
                            Js.Nullable.null
                        }
                        route>
                        ...childrenProps
                      </Link>
                  }
                  title=article->titleGet
                  content=article->contentGet
                  cardHeight=420
                  date=
                    article
                    ->datePublishedGet
                    ->MomentRe.moment
                    ->MomentRe.Moment.(fromNow(~withoutSuffix=Some(false)))
                  username=article->ownerGet->usernameGet->Js.Nullable.toOption
                  userAvatar=article->ownerGet->avatarGet->Js.Nullable.toOption
                  userId=article->ownerGet->ownerIdGet
                />;
              },
              articles,
            )
            |> ReasonReact.array
          }
        </div>
      </div>
    },
};

[@bs.deriving abstract]
type jsProps = {
  name: string,
  description: Js.Nullable.t(string),
  articles: Js.Nullable.t(array(article)),
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~name=jsProps->nameGet,
      ~description=
        Belt.Option.getWithDefault(
          jsProps->descriptionGet |> Js.Nullable.toOption,
          "",
        ),
      ~articles=jsProps |> articlesGet |> Js.Nullable.toOption,
      [||],
    )
  );