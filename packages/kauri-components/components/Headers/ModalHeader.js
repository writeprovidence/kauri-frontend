// @flow
import * as React from 'react'
import styled from 'styled-components'

const Container = styled.div`
  display: flex;
  align-items: center;
  > :first-child {
    margin-right: auto;
  }
`;

type Props = {
  title: React.Node,
  actions: React.Element<React.StatelessFunctionalComponent<{}>>
}

export default ({ title, actions }: Props) =>
  <Container>
    {title}
    {actions}
  </Container>
