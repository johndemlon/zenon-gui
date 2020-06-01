
#include<applications/telnet.h>

using namespace kayos::common;
using namespace kayos::protocols::ethernet;

namespace kayos
{
    namespace applications
    {

        ConnectButtonEventHandler::ConnectButtonEventHandler(TelnetClient* target)
        {
            this->target = target;
        }
        ConnectButtonEventHandler::~ConnectButtonEventHandler()
        {
        }
        void ConnectButtonEventHandler::OnClick(graphicalobjects::Button*)
        {
            target->ConnectButtonClicked();
        }





        SendButtonEventHandler::SendButtonEventHandler(TelnetClient* target)
        {
            this->target = target;
        }
        SendButtonEventHandler::~SendButtonEventHandler()
        {
        }
        void SendButtonEventHandler::OnClick(graphicalobjects::Button*)
        {
            target->SendButtonClicked();
        }




        TelnetClient::TelnetClient(uint32_t width, uint32_t height, TransmissionControlProtocolHandler* handler)
         :  GraphicalObjectContainer(0,0,width,height),
            TransmissionControlProtocolPayloadHandler(),
            connectButtonEventHandler(this),
            sendButtonEventHandler(this),
            ipAddressLabel(0,0,20,10,"IP"),
            ipAddressTextBox(ipAddressLabel.GetPosition().left+ipAddressLabel.GetPosition().width, ipAddressLabel.GetPosition().top, width-ipAddressLabel.GetPosition().left-ipAddressLabel.GetPosition().width-36, ipAddressLabel.GetPosition().height),
            connectButton(ipAddressTextBox.GetPosition().left+ipAddressTextBox.GetPosition().width, ipAddressTextBox.GetPosition().top, 36, ipAddressTextBox.GetPosition().height, "conn"),
            messageTextBox(ipAddressLabel.GetPosition().left,ipAddressLabel.GetPosition().top+ipAddressLabel.GetPosition().height,width - 2*ipAddressLabel.GetPosition().left, height - ipAddressLabel.GetPosition().top - 2*ipAddressLabel.GetPosition().height),
            sendButton(ipAddressLabel.GetPosition().left, height-ipAddressLabel.GetPosition().height, width - 2*ipAddressLabel.GetPosition().left, ipAddressLabel.GetPosition().height, "send")
        {
            this->transmissionControlProtocolHandler = handler;
            connection = 0;
            AddChild(&ipAddressLabel);
            AddChild(&ipAddressTextBox);
            AddChild(&connectButton);
            AddChild(&messageTextBox);
            AddChild(&sendButton);

            connectButton.ConnectEventHandler(&connectButtonEventHandler);
            sendButton.ConnectEventHandler(&sendButtonEventHandler);
        }

        TelnetClient::~TelnetClient()
        {
        }

        void TelnetClient::ConnectButtonClicked()
        {
            if(connection == 0)
            {
                if(transmissionControlProtocolHandler != 0)
                {
                    connection = transmissionControlProtocolHandler->Connect(ipAddressTextBox.GetText());
                    if(connection != 0)
                        connection->ConnectTransmissionControlProtocolPayloadHandler(this);
                }
            }
            else
            {
                connection->Disconnect();
                connection = 0;
            }
        }

        void TelnetClient::SendButtonClicked()
        {
            if(connection == 0)
                return;
            if(!connection->IsConnected())
                return;

            connection->Send(messageTextBox.GetText());
            connection->Send("\r\n");
            messageTextBox.SetText("");
        }

        void TelnetClient::HandleTransmissionControlProtocolPayload(TransmissionControlProtocolConnection* connection, uint8_t* data, uint32_t length)
        {
            TransmissionControlProtocolPayloadHandler::HandleTransmissionControlProtocolPayload(connection, data, length);
            data[length-1] = '\0';
            messageTextBox.SetText((char*)data);
        }


    }
}

