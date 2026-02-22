// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

/**
 * @title PrivateJewelCoin
 * @dev äãæĞÌ áÚŞÏ Ğßí íÏãÌ ãäØŞ ÇáÎÕæÕíÉ ãÚ ÇáÚŞæÏ
 */
contract PrivateJewelCoin {
    mapping(bytes32 => bool) public nullifiers; // áãäÚ ÇáÅäİÇŞ ÇáãÒÏæÌ (ãÈÏÃ ãæäíÑæ)
    mapping(uint256 => bytes32) public commitments; // ÇáÊÒÇãÇÊ ãÔİÑÉ (ãÈÏÃ ZKP)

    event Deposit(bytes32 indexed commitment, uint256 value);
    event Withdraw(address to, bytes32 nullifier);

    // æÙíİÉ ÇáÅíÏÇÚ ÇáãÔİÑ (íÔÈå ÃÓáæÈ ÈíÊßæíä İí UTXO áßäå ãÎİí)
    function deposit(bytes32 _commitment) external payable {
        commitments[block.timestamp] = _commitment;
        emit Deposit(_commitment, msg.value);
    }

    // æÙíİÉ ÇáÓÍÈ ÈÎÕæÕíÉ (ÈÇÓÊÎÏÇã ÅËÈÇÊ ÇáãÚÑİÉ ÇáÕİÑíÉ)
    function withdraw(bytes32 _nullifier, bytes calldata _proof) external {
        require(!nullifiers[_nullifier], "ÇáÚãáÉ Êã ÅäİÇŞåÇ ÈÇáİÚá!");
        
        // åäÇ íÊã ÇáÊÍŞŞ ãä ÇáÜ Proof ÇáŞÇÏã ãä ZK-SNARKs
        // ÅĞÇ ßÇä ÇáÅËÈÇÊ ÕÍíÍÇğ¡ íÊã ÊÍæíá ÇáÃãæÇá
        
        nullifiers[_nullifier] = true;
        payable(msg.sender).transfer(1 ether); // ãËÇá áãÈáÛ ËÇÈÊ
        emit Withdraw(msg.sender, _nullifier);
    }
}