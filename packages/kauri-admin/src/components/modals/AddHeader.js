import React, { Component } from 'react';
import { Modal, Button, Tabs, Tab, FormControl } from 'react-bootstrap';
import Configuration from '../Configuration';


class AddArticle extends Component {
    constructor(props) {
        super(props);
        this.state = {
            articles: [],
            selected_id: '',
        }
        this.fetchArticles = this.fetchArticles.bind(this);
    }

    async fetchArticles(e) {
        if (e.target.value.length >= 3) {
            const articles = await this.props.searchArticles({ val: e.target.value });
            this.setState({ articles: articles.content });
        }
    }

    handleChange(id) {
        this.setState({ selected_id: id });
        this.props.handleChange({ type: 'ARTICLE', id: id });
    }

    render() {
        return (
            <div>
                <FormControl
                    type="text"
                    value={this.state.value}
                    placeholder="Search Article"
                    onChange={this.fetchArticles}
                />
                <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'flex-start' }}>
                    {this.state.articles.length > 0 && this.state.articles.map(i =>
                        <Button
                            onClick={() => this.handleChange(i.id)}
                            bsStyle="link"
                            style={{ backgroundColor: this.state.selected_id === i.id ? '#5bc0de' : 'transparent', outline: 'none' }}
                            key={i.id}>
                            {i.title}
                        </Button>
                    )}
                </div>
            </div>);
    }
}

class AddCollection extends Component {
    constructor(props) {
        super(props);
        this.state = {
            collections: [],
            selected_id: '',
        }
        this.fetchCollections = this.fetchCollections.bind(this);
    }

    async fetchCollections(e) {
        if (e.target.value.length >= 1) {
            const collections = await this.props.searchCollections({ val: e.target.value });
            this.setState({ collections: collections.content });
        }
    }

    handleChange(id) {
        this.setState({ selected_id: id });
        this.props.handleChange({ type: 'COLLECTION', id: id });
    }

    render() {
        return (
            <div>
                <FormControl
                    type="text"
                    value={this.state.value}
                    placeholder="Search Collection"
                    onChange={this.fetchCollections}
                />
                <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'flex-start' }}>
                    {this.state.collections.length > 0 && this.state.collections.map(i =>
                        <Button
                            onClick={() => this.handleChange(i.id)}
                            bsStyle="link"
                            style={{ backgroundColor: this.state.selected_id === i.id ? '#5bc0de' : 'transparent', outline: 'none' }}
                            key={i.id}>
                            {i.name}
                        </Button>
                    )}
                </div>
            </div>);
    }
}

class AddHeader extends Component {
    constructor(props) {
        super(props);
        this.state = {
            type: null,
            id: null,
        };
        this.handleChange = this.handleChange.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    handleChange(payload) {
        const { type, id } = payload;
        this.setState({ type, id });
    }

    handleSubmit() {
        const { type, id } = this.state;
        if (type && type.length > 0 && id && id.length > 0) this.props.addHeader({
            id: this.props.selectedList,
            header: { id, type }
        });
    }

    render() {
        return (
            <Modal show={this.props.show} onHide={this.props.closeModal}>
                <Modal.Header closeButton>
                    <Modal.Title>Add Header</Modal.Title>
                </Modal.Header>
                <Modal.Body>
                    <Tabs defaultActiveKey={1} id="uncontrolled-tab-example">
                        <Tab style={{ padding: 20 }} eventKey={1} title="Article">
                            <AddArticle handleChange={this.handleChange} searchArticles={this.props.searchArticles} />
                        </Tab>
                        <Tab style={{ padding: 20 }} eventKey={3} title="Collection">
                            <AddCollection handleChange={this.handleChange} searchCollections={this.props.searchCollections} />
                        </Tab>
                    </Tabs>
                </Modal.Body>
                <Modal.Footer>
                    <Button onClick={this.props.closeModal}>Cancel</Button>
                    <Button onClick={this.handleSubmit} bsStyle="primary">Add Header</Button>
                </Modal.Footer>
            </Modal>);
    }
};

export default AddHeader;