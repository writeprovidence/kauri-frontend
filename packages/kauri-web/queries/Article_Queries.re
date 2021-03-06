module GetArticle = [%graphql
  {|
    query getArticle($id: String!, $version: Int!) {
      getArticle(id: $id, version: $version) {
        id
        version
        title
        content
        dateCreated
        datePublished
        status
        attributes
        contentHash
        checkpoint
        vote {
          totalVote
        }
        author {
          id
          name
          avatar
          username
        }
        comments {
          content {
            author {
              id
              name
              avatar
              username
            }
            posted
            body
          }
          totalPages
          totalElements
        }
        resourceIdentifier {
          id
          type
          version
        }
      }
    }
  |}
];

module GetArticleQuery = ReasonApollo.CreateQuery(GetArticle);

module ApproveArticle = [%graphql
  {|
    mutation approveArticle($article_id: String!, $version: Int!, $signature: String!) {
      approveArticle(id: $article_id, version: $version, signature: $signature) {
         hash
      }
    }
  |}
];

module ApproveArticleMutation = ReasonApollo.CreateMutation(ApproveArticle);

module DraftArticle = [%graphql
  {|
    mutation submitArticleVersion($id: String, $subject: String, $text: String, $attributes: Map_String_StringScalar) {
      submitArticle (id: $id, title: $subject, content: $text, attributes: $attributes) {
        hash
      }
    }
  |}
];

module DraftArticleMutation = ReasonApollo.CreateMutation(DraftArticle);

module PublishArticle = [%graphql
  {|
    mutation publishArticle($id: String, $version: Int, $owner: ResourceIdentifierInput, $signature: String) {
      publishArticle (id: $id, version: $version, owner: $owner, signature: $signature) {
        hash
      }
    }
  |}
];

module PublishArticleMutation = ReasonApollo.CreateMutation(PublishArticle);

module SearchPersonalArticles = [%graphql
  {|
    query searchPersonalArticles($userId: String) {
      searchArticles (filter: { authorIdEquals: $userId, statusIn: [ PUBLISHED ], latestVersion: true } ) {
        content {
            id, version, title, content, dateCreated, datePublished, author {
            id, name avatar username
          }
          status, attributes, contentHash, checkpoint, vote { totalVote }, comments { content { posted author { id, name avatar username }, body }, totalPages, totalElements  }
          resourceIdentifier { type, id, version }
        }
        totalPages totalElements
      }
    }
  |}
];

module SearchPersonalArticlesQuery =
  ReasonApollo.CreateQuery(SearchPersonalArticles);

module GetArticles = [%graphql
  {|
    query searchArticles {
        searchArticles (filter: { statusIn: [PUBLISHED], latestVersion: true }) {
            content {
              id, version, title, content, dateCreated, datePublished, author {
                id, name username avatar }
                 status, attributes, contentHash, checkpoint, vote { totalVote }, comments { content { posted author { id, name avatar username }, body }, totalPages, totalElements  }
                 resourceIdentifier { type, id, version }             }
            totalPages
            totalElements
        }
    }
|}
];

module GetArticlesQuery = ReasonApollo.CreateQuery(GetArticles);

module SearchCommunityArticles = [%graphql
  {|
    query searchCommunityArticles($category: String) {
        searchArticles (filter: { statusIn: [PUBLISHED], latestVersion: true, ownerEquals: $category }) {
            content {
              id, version, title, content, dateCreated, datePublished
              author {
                id
                 name
                 avatar
                 username
              }
              status, attributes, contentHash, checkpoint,
               vote { totalVote },
               comments {
                 content { posted author { id, name avatar username }, body }, totalPages, totalElements
              }
              resourceIdentifier { type, id, version }
            }
            totalPages
            totalElements
        }
    }
  |}
];

module SearchCommunityArticlesQuery =
  ReasonApollo.CreateQuery(SearchCommunityArticles);

module CommunityArticlesCount = [%graphql
  {|
    query communityArticlesCount($category: String) {
        searchArticles (filter: { statusIn: [PUBLISHED], latestVersion: true, ownerEquals: $category }) {
            content {
              id
            }
            totalElements
        }
    }
  |}
];

module CommunityArticlesCountQuery =
  ReasonApollo.CreateQuery(CommunityArticlesCount);