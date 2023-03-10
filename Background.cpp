#include "Background.h"
#include "Game.hpp"

Background::Background(Game* game): Entity(game)
{
	mSprite = "Ocean";
}

unsigned Background::getCategory() const
{
	return Category::Terrain;
}

void Background::Repeat(float endDist, float startPos)
{
	if (this->getWorldPosition().z > endDist)
	{
		this->setPosition(0.0f, 0.0f, startPos);
	}
}

void Background::drawCurrent() const
{

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = game->mCurrFrameResource->ObjectCB->Resource();
	auto matCB = game->mCurrFrameResource->MaterialCB->Resource();

	game->mCommandList->IASetVertexBuffers(0, 1, &renderer->Geo->VertexBufferView());
	game->mCommandList->IASetIndexBuffer(&renderer->Geo->IndexBufferView());
	game->mCommandList->IASetPrimitiveTopology(renderer->PrimitiveType);

	//step18
	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(game->mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	tex.Offset(renderer->Mat->DiffuseSrvHeapIndex, game->mCbvSrvDescriptorSize);

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + renderer->ObjCBIndex * objCBByteSize;
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + renderer->Mat->MatCBIndex * matCBByteSize;

	game->mCommandList->SetGraphicsRootDescriptorTable(0, tex);
	game->mCommandList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	game->mCommandList->SetGraphicsRootConstantBufferView(3, matCBAddress);
	game->mCommandList->DrawIndexedInstanced(renderer->IndexCount, 1, renderer->StartIndexLocation, renderer->BaseVertexLocation, 0);
}

void Background::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(10.0f, 10.0f, 10.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["Ocean"].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}

void Background::updateCurrent(const GameTimer& gt)
{
	Entity::updateCurrent(gt);

	if (this->getWorldPosition().z > 50.0f)
	{
		this->setPosition(0.0f, 0.0f, 30.0f);
	}

	this->setVelocity(XMFLOAT3(0.0, 0.0, 8.0));

}
