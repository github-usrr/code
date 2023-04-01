import io.netty.bootstrap.Bootstrap;
import io.netty.channel.*;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioDatagramChannel;
import io.netty.handler.codec.dns.*;
import io.netty.util.internal.SocketUtils;
import io.netty.buffer.Unpooled;

public class DnsServer {

    String addr;
    int port;
    public DnsServer(final String addr, final int port) {
        this.addr = addr;
        this.port = port;
        start();
    }

    private void start() {
        EventLoopGroup eventLoopGroup = new NioEventLoopGroup();

        try {
            Bootstrap b = new Bootstrap();
            b.group(eventLoopGroup)
                    .channel(NioDatagramChannel.class)
                    .handler(new ChannelInitializer<NioDatagramChannel>() {
                        @Override
                        public void initChannel(NioDatagramChannel ch) throws Exception {
                            ch.pipeline().addLast(new DatagramDnsQueryDecoder());
                            ch.pipeline().addLast(new DatagramDnsResponseEncoder());
                            ch.pipeline().addLast(new DnsHandler());
                        }
                    });

            ChannelFuture cf = b.bind(port).sync();
            System.out.println("DNS-Server started at port " + port);

            cf.channel().closeFuture().sync();

        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            eventLoopGroup.shutdownGracefully();
        }
    }

    private class DnsHandler extends SimpleChannelInboundHandler<DatagramDnsQuery> {

        @Override
        protected void channelRead0(ChannelHandlerContext ctx, DatagramDnsQuery query) throws Exception {

            DatagramDnsResponse response = new DatagramDnsResponse( query.recipient(),
                                                                    query.sender(),
                                                                    query.id() );

            DefaultDnsQuestion dnsQuestion = query.recordAt(DnsSection.QUESTION);
            response.addRecord(DnsSection.QUESTION, dnsQuestion);

            if ( dnsQuestion.name().equals("example.com.") ) {

                byte[] rawIp = SocketUtils.addressByName(addr).getAddress();
                DefaultDnsRawRecord queryAnswer = new DefaultDnsRawRecord( "exampleresponse.com",
                                                                            DnsRecordType.A,
                                                                            3600,
                                                                            Unpooled.wrappedBuffer(rawIp) );
                response.addRecord(DnsSection.ANSWER, queryAnswer);

            } else {
                response.setCode(DnsResponseCode.BADNAME);
            }

            ctx.writeAndFlush(response);
        }

        @Override
        public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
            cause.printStackTrace();
        }
    }
}