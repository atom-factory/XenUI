// Author: Jake Rieger
// Created: 8/3/2024.
//

#include "Context.h"

namespace XenUI {
    Context::Context(HWND hwnd) : m_Hwnd(hwnd) {
        if (!hwnd) {
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
        }

        ThrowIfFailed(
          D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&m_pFactory)));

        RECT rc;
        ::GetClientRect(hwnd, &rc);
        ThrowIfFailed(m_pFactory->CreateHwndRenderTarget(
          D2D1::RenderTargetProperties(),
          D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom)),
          &m_pRenderTarget));

        ThrowIfFailed(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                          __uuidof(IDWriteFactory),
                                          CAST<IUnknown**>(&m_pDWriteFactory)));
    }

    Context::~Context() {
        if (m_pRenderTarget) {
            m_pRenderTarget.Reset();
        }

        if (m_pFactory) {
            m_pFactory.Reset();
        }
    }

    void Context::Resize(int width, int height) const {
        if (m_pRenderTarget) {
            ThrowIfFailed(m_pRenderTarget->Resize(D2D1_SIZE_U(width, height)));
        }
    }

    void Context::DrawRect(const Offset& position,
                           const Size<>& size,
                           const Color& color,
                           const bool rounded,
                           const f32 borderRadius) const {
        if (!m_pRenderTarget) {
            return;
        }

        ID2D1SolidColorBrush* fillBrush = nullptr;
        ThrowIfFailed(m_pRenderTarget->CreateSolidColorBrush(color.GetD2DColor(), &fillBrush));

        const auto rect = Rectangle::FromCenter(position, size.Width, size.Height);
        if (rounded) {
            m_pRenderTarget->FillRoundedRectangle(rect.ToD2DRectRounded(borderRadius), fillBrush);
        } else {
            m_pRenderTarget->FillRectangle(rect.ToD2DRect(), fillBrush);
        }
        fillBrush->Release();
    }

    void Context::DrawRect(const Rectangle& rect,
                           const Color& fillColor,
                           const StrokeProperties& stroke,
                           const bool rounded,
                           const f32 borderRadius) const {
        if (!m_pRenderTarget) {
            return;
        }

        ID2D1SolidColorBrush* fillBrush = nullptr;
        ThrowIfFailed(m_pRenderTarget->CreateSolidColorBrush(fillColor.GetD2DColor(), &fillBrush));
        ID2D1SolidColorBrush* strokeBrush = nullptr;
        ThrowIfFailed(
          m_pRenderTarget->CreateSolidColorBrush(stroke.color.GetD2DColor(), &strokeBrush));

        if (rounded) {
            m_pRenderTarget->FillRoundedRectangle(rect.ToD2DRectRounded(borderRadius), fillBrush);
            m_pRenderTarget->DrawRoundedRectangle(rect.ToD2DRectRounded(borderRadius),
                                                  strokeBrush,
                                                  stroke.width);
        } else {
            m_pRenderTarget->FillRectangle(rect.ToD2DRect(), fillBrush);
            m_pRenderTarget->DrawRectangle(rect.ToD2DRect(), strokeBrush, stroke.width);
        }
        fillBrush->Release();
    }

    void Context::DrawString(const std::string& text,
                             f32 fontSize,
                             const Offset& position,
                             const Size<f32>& size,
                             const Color& color) const {
        if (!m_pRenderTarget || !m_pDWriteFactory) {
            return;
        }

        IDWriteTextFormat* format = nullptr;
        ThrowIfFailed(m_pDWriteFactory->CreateTextFormat(L"Segoe UI",
                                                         nullptr,
                                                         DWRITE_FONT_WEIGHT_NORMAL,
                                                         DWRITE_FONT_STYLE_NORMAL,
                                                         DWRITE_FONT_STRETCH_EXPANDED,
                                                         fontSize,
                                                         L"en-us",
                                                         &format));
        ThrowIfFailed(format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER));
        ThrowIfFailed(format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER));

        ID2D1SolidColorBrush* brush = nullptr;
        ThrowIfFailed(m_pRenderTarget->CreateSolidColorBrush(color.GetD2DColor(), &brush));

        wstr wText;
        ANSIToWide(text, wText);
        m_pRenderTarget->DrawText(
          wText.c_str(),
          wcslen(wText.c_str()),
          format,
          Rectangle::FromCenter(position, size.Width, size.Height).ToD2DRect(),
          brush);

        brush->Release();
        format->Release();
    }
}  // namespace XenUI