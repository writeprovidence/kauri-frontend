module.exports = {
  extends: ['standard', 'standard-react', 'plugin:flowtype/recommended'],
  plugins: ['flowtype', 'jest', 'graphql'],
  rules: {
    'no-debugger': 0,
    'react/no-unused-prop-types': 0,
    'react/prop-types': 0,
    semi: 0,
    'react/jsx-filename-extension': [1, { extensions: ['.js', '.jsx'] }],
    'graphql/template-strings': [
      'warn',
      {
        env: 'apollo',
        schemaJson: require('./schema.json'),
      },
    ],
    'comma-dangle': ['error', 'always-multiline'],
  },
  env: {
    'jest/globals': true,
  },
  globals: {
    artifacts: true,
    contract: true,
    assert: true,
    cy: true,
    context: true,
    Cypress: true,
    document: true,
    window: true,
  },
}
