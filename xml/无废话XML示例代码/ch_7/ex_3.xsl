<?xml version="1.0" encoding="GB2312" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- IE5  ֻ���� <xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl"> -->

<!-- IE5 ������ xsl:output -->
<xsl:output encoding="GB2312"/>

<xsl:template match="/">
  <html>
  <head>
  <title>��Ʒ��Ѱ���</title>
  </head>
  <body>
    <h1>��Ʒ��Ѱ���</h1>
    <p><b>ժҪ��</b><xsl:value-of select="*/ժҪ"/></p>
    <xsl:apply-templates select="��Ʒ��Ѱ"/>
  </body>
  </html>
</xsl:template>

<xsl:template match="��Ʒ��Ѱ">
  <table>
    <tr>
      <th>Ʒ��</th>
      <th>����</th>
      <th>˵��ҳ</th>
    </tr>
  <xsl:for-each select="��Ʒ">
    <tr>
      <td><xsl:value-of select="Ʒ��"/></td>
      <td><xsl:value-of select="����"/></td>
      <td><a href="{˵��ҳ/@��ַ}"><xsl:value-of select="˵��ҳ"/></a></td>
      <!-- IE5 ֻ���� <td><a><xsl:attribute name="href"><xsl:value-of select="˵��ҳ/@��ַ"/></xsl:attribute><xsl:value-of select="˵��ҳ"/></a></td> -->
    </tr>
  </xsl:for-each>
  </table>
</xsl:template>
</xsl:stylesheet>
