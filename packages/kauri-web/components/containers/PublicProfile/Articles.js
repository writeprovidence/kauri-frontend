// @flow
import React from 'react'
import styled from 'styled-components'
import moment from 'moment';
import ArticleCard from '../../../../kauri-components/components/Card/ArticleCard';
import Empty from './Empty';
import { Link } from '../../../routes';
import ContentContainer from './PublicProfileContentContainer';

import type { ArticlesProps } from './types';

const ArticlesConntainer = styled.div`
    display: flex;
    flex-direction: row;
    justify-content: center;
    flex: 1;
    flex-wrap: wrap;
    > div {
      margin: ${props => props.theme.space[2]}px;
    }
`

const Articles = ({ articles, type, routeChangeAction }: ArticlesProps) =>
  articles.content.length > 0
    ? <ContentContainer>
      <ArticlesConntainer>
        {articles.content.map(article =>
          <ArticleCard
            key={`${article.id}-${article.version}`}
            changeRoute={routeChangeAction}
            date={moment(article.dateCreated).format('D MMM YYYY')}
            title={article.title}
            content={article.content}
            userId={type !== 'toBeApproved' && article.owner ? article.owner.id : article.author.id}
            username={type !== 'toBeApproved' && article.owner ? (article.owner.name || article.owner.username) : (article.author.name || article.author.username)}
            userAvatar={type !== 'toBeApproved' && article.owner ? article.owner.avatar : article.author.avatar}
            id={article.id}
            version={article.version}
            cardHeight={500}
            imageURL={article.attributes && article.attributes.background}
            linkComponent={(childrenProps, route) => (
              <Link toSlug={route.includes('article') && article.title} useAnchorTag href={route}>
                {childrenProps}
              </Link>
            )}
          />)}
      </ArticlesConntainer>
    </ContentContainer> : <Empty />;

export default Articles;