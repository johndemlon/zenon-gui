
#ifndef __APPLICATIONS__TELNET_H
    #define __APPLICATIONS__TELNET_H

    #include<common/string.h>
    #include<graphicalobjects/window.h>
    #include<graphicalobjects/textbox.h>
    #include<graphicalobjects/button.h>
    #include<graphicalobjects/label.h>

    #include<protocols/ethernet/transmissioncontrolprotocol.h>

    namespace kayos
    {
        namespace applications
        {

            class TelnetClient;

            class ConnectButtonEventHandler : public graphicalobjects::ButtonEventHandler
            {
                protected:
                    TelnetClient* target;
                public:
                    ConnectButtonEventHandler(TelnetClient* target);
                    ~ConnectButtonEventHandler();
                    void OnClick(graphicalobjects::Button* sender);
            };

            class SendButtonEventHandler : public graphicalobjects::ButtonEventHandler
            {
                protected:
                    TelnetClient* target;
                public:
                    SendButtonEventHandler(TelnetClient* target);
                    ~SendButtonEventHandler();
                    void OnClick(graphicalobjects::Button* sender);
            };

            class TelnetClient : public graphicalobjects::GraphicalObjectContainer,
                                 public protocols::ethernet::TransmissionControlProtocolPayloadHandler
            {
                protected:
                    ConnectButtonEventHandler connectButtonEventHandler;
                    SendButtonEventHandler sendButtonEventHandler;

                    graphicalobjects::Label ipAddressLabel;
                    graphicalobjects::TextBox ipAddressTextBox;
                    graphicalobjects::Button connectButton;

                    graphicalobjects::TextBox messageTextBox;
                    graphicalobjects::Button sendButton;

                    protocols::ethernet::TransmissionControlProtocolConnection* connection;
                    protocols::ethernet::TransmissionControlProtocolHandler* transmissionControlProtocolHandler;

                public:
                    TelnetClient(uint32_t width, uint32_t height, protocols::ethernet::TransmissionControlProtocolHandler* handler);
                    ~TelnetClient();

                    void ConnectButtonClicked();
                    void SendButtonClicked();
                    virtual void HandleTransmissionControlProtocolPayload(protocols::ethernet::TransmissionControlProtocolConnection* connection, uint8_t* data, uint32_t length);
            };

        }
    }

#endif
