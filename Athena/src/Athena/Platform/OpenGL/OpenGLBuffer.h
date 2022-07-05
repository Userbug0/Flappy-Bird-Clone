#pragma once

#include "Athena/Renderer/Buffer.h"


namespace Athena
{
	class ATHENA_API OpenGLVertexBuffer: public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;

		void SetData(const void* data, uint32_t size) override;

		inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		inline const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};


	class ATHENA_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t �ount);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;

		inline uint32_t GetCount() const override { return m_Count; };
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}
