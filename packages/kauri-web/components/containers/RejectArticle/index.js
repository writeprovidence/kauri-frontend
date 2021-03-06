import RejectArticle from './View.js'
import { routeChangeAction } from '../../../lib/Module'
import { getArticle } from '../../../queries/Article'
import { connect } from 'react-redux'
import { compose, graphql } from 'react-apollo'
import withLoading from '../../../lib/with-loading'
import { rejectArticleAction } from '../Article/Module'

const mapStateToProps = (state, ownProps) => {
  return {}
}

export default compose(
  connect(
    mapStateToProps,
    {
      routeChangeAction,
      rejectArticleAction,
    }
  ),
  graphql(getArticle, {
    options: ({ article_id, article_version }) => ({ variables: { article_id, article_version } }),
  }),
  withLoading()
)(RejectArticle)
