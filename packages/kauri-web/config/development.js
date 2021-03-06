// const monolithApi = '35.196.21.146:80'
const monolithApi = process.env.MONOLITH_API
const monolithExternalApi = 'api.dev2.kauri.io'

module.exports = {
  monolithApi,
  monolithExternalApi,
  gethBlockchain: '35.231.60.112:8545',
  KauriCoreArtifact: '../../../../flow/smart-contracts/build/contracts/KauriCore.json',
  WalletArtifact: '../../../../flow/smart-contracts/build/contracts/Wallet.json',
  TopicModeratorArtifact: '../../../../flow/smart-contracts/build/contracts/TopicModerator.json',
  KauriCommunityId: '8241ec73308348c890f19a9cdffc50cb',
}

// module.exports = {
//   monolithApi: 'localhost:8080',
//   gethBlockchain: 'localhost:8545',
//   KauriCoreArtifact: '/Users/rej156/Documents/flow/smart-contracts/build/contracts/KauriCore.json',
//   monolithExternalApi: 'localhost:8080',
// }
